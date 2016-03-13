Gem::Specification.new do |s|
  s.name    = 'rbscws'
  s.version = '0.8'
  s.licenses    = ['Apache-2.0']
  s.date    = '2010-07-14'
  s.rubyforge_project = "rbscws"

  s.summary = "A Ruby interface to the Scws,abber for Simple Chinese Word Segment "
  s.description = "A Ruby interface to the Scws,Ported from pyscws."

  s.authors  = ['mooosu']
  s.email    = 'mooosu@hotmail.com'
  s.homepage = 'https://github.com/mooosu'

  s.has_rdoc = false

  s.files = Dir.glob("lib/scws/extconf.rb")
  s.files += Dir.glob("lib/scws/scws.c")
  s.files += Dir.glob("lib/*.rb")
  s.extensions << 'lib/scws/extconf.rb'

  s.rdoc_options << '--title' << 'Rbscws' <<
    '--main' << 'README.rdoc' <<
    '--line-numbers'

  s.extra_rdoc_files = ["LICENSE"]
end
