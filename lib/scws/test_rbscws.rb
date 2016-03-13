#encoding: utf-8
require 'rbscws.so'
path="/sourcecode/public_svn/zhaoia/trunk/data/scws_dict/dict.short.xdb"
s = Scws::Scws.new
s.set_charset("utf-8")
s.add_dict(path,1)
puts s.cws("找呀在这里")
puts s.cws("今天是星期一")
