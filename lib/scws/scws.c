// Include the Ruby headers and goodies
#include "ruby.h"
#include "ruby/encoding.h"

#ifdef __APPLE__
#include "scws/scws.h"
#else
#include "scws.h"
#endif
#define _VERBOSE 1

VALUE mScws;
VALUE mScwsError;
VALUE eInitializeError;
void init_scws_errors() {
}
VALUE cScws;
int debug_mode;
typedef struct {
  scws_t scws;
}Scws;
static void rbscws_free(Scws* pobj)
{
  scws_free(pobj->scws);
  free( pobj);
}
static VALUE t_initialize( )
{
  if( debug_mode ){
    printf("t_initialize\n");
  }
  Scws * pobj =ALLOC(Scws);
  if ( pobj) {
    pobj->scws= scws_new();
    if( !pobj->scws ){
      rb_raise( eInitializeError,"%s\n","Canot init scws");
    } else {
      scws_set_charset(pobj->scws, "utf8");
    }

  }
  return Data_Wrap_Struct(cScws,0,rbscws_free,pobj);
}
static VALUE t_set_charset(VALUE self, VALUE charset)
{

  Scws * pobj ;
  char *str = RSTRING_PTR(charset);
  Data_Get_Struct(self,Scws,pobj);
  scws_set_charset(pobj->scws, str);
  if( debug_mode ){
    printf("charset:%s\n",str);
  }
  rb_iv_set(self, "@charset",charset);
  return self;
}
static VALUE t_set_dict(VALUE self, VALUE fpath , VALUE mode)
{

  Scws * pobj ;
  char *str = RSTRING_PTR(fpath);
  int m =FIX2INT(mode);
  Data_Get_Struct(self,Scws,pobj);
  scws_set_dict(pobj->scws, str,m);
  return self;
}

static VALUE t_add_dict(VALUE self, VALUE fpath , VALUE mode)
{

  Scws * pobj ;
  char *str = RSTRING_PTR(fpath);
  int m =FIX2INT(mode);
  Data_Get_Struct(self,Scws,pobj);
  scws_add_dict(pobj->scws, str,m);
  if( debug_mode ){
    printf("fpath:%s  ,   mode:%d\n",str,m);
  }
  return self;
}
static VALUE t_cws(VALUE self, VALUE string )
{
  Scws * pobj ;
  VALUE word;
  VALUE word_list = rb_ary_new();

  char *str = RSTRING_PTR(string);
  Data_Get_Struct(self,Scws,pobj);
  scws_res_t res,cur;
  scws_send_text(pobj->scws,str,strlen(str));
  while(( cur = res = scws_get_result( pobj->scws ) )!=NULL) {
    while ( cur != NULL ){
      word=rb_str_new(str+cur->off,cur->len);
      ENCODING_SET(word,rb_utf8_encindex());
      rb_ary_push(word_list,word);
      cur=cur->next;
    }
    scws_free_result(res);
  }
  return word_list;
}
static VALUE t_cws_org(VALUE self, VALUE string )
{
  Scws * pobj ;
  VALUE word,word_attr;
  VALUE word_list = rb_ary_new();
  VALUE word_pair;

  char *str = RSTRING_PTR(string);
  Data_Get_Struct(self,Scws,pobj);
  scws_res_t res,cur;
  scws_send_text(pobj->scws,str,strlen(str));
  while(( cur = res = scws_get_result( pobj->scws ) )!=NULL) {
    while ( cur != NULL ){
      word=rb_str_new(str+cur->off,cur->len);
      word_attr =rb_str_new2(cur->attr);
      word_pair = rb_ary_new();
      rb_ary_push(word_pair,word);
      rb_ary_push(word_pair,word_attr);
      rb_ary_push(word_list,word_pair);
      cur=cur->next;
    }
    scws_free_result(res);
  }
  return word_list;
}
void Init_rbscws() {
  VALUE dm= rb_gv_get("$DEBUG");
  debug_mode=  dm == Qtrue;
  if ( debug_mode )
    printf("debug_mode %d\n", debug_mode);
  mScws = rb_define_module("Scws");
  cScws= rb_define_class_under(mScws,"Scws", rb_cObject);

  mScwsError = rb_define_class_under(mScws, "mScwsError", rb_eRuntimeError);
  eInitializeError = rb_define_class_under(mScws, "ScwsInitializeError", mScwsError);

  rb_define_singleton_method(cScws, "new", t_initialize, 0);
  rb_define_method(cScws, "set_charset", t_set_charset, 1);
  rb_define_method(cScws, "set_dict", t_set_charset, 2);
  rb_define_method(cScws, "add_dict", t_add_dict, 2);
  //rb_define_method(cScws, "set_rules", t_set_charset, 1);
  //rb_define_method(cScws, "set_ignore", t_set_charset, 1);
  rb_define_method(cScws, "cws", t_cws, 1);
  rb_define_method(cScws, "cws_org", t_cws_org, 1);
  rb_define_const(mScws,"XDICT_XDB",SCWS_XDICT_XDB);
  rb_define_const(mScws,"XDICT_MEM",SCWS_XDICT_MEM);
  rb_define_const(mScws,"XDICT_TXT",SCWS_XDICT_TXT);
  if( debug_mode ){
    printf("%s\n","Init_rbscws completed");
  }
}

