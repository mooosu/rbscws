#encoding: utf-8
require 'scws/rbscws'
if $0 == __FILE__
  $KCODE='u'
  path="/sourcecode/new_public_svn/zhaoia/trunk/data/scws_dict/dict.short.xdb"
  s = Scws::Scws.new
  s.set_charset("utf-8")
  s.add_dict(path,1)
  puts s.cws("找呀是一个垂直搜索引擎,网址是http://www.zhaoia.com")
  puts s.cws_org("找呀是一个垂直搜索引擎,网址是http://www.zhaoia.com")
end
