# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

# Give it a name
extension_name = 'rbscws'

# The destination
dir_config(extension_name)
dir_config("scws")
if RUBY_VERSION =~/1.9/
  $CFLAGS << " -DRUBY_19"
end

# Do the work
have_library("scws","scws_new")
create_makefile(extension_name)
