egged, the egg editor
=====================
like `ed` but less useful:

- two modes: insert and command

- four commands:
  - (a)ppend
  - repla(c)e
  - (p)rint
  - (w)rite

- (a) takes a single address, (c) and (p) take ranges

- the default address for (c) and (p) is the entire document, and the default address for (a) is the end

- (w) takes one or zero arguments:
  - if `arg[1]` is supplied, no arguments writes to that file
  - if `arg[1]` is not supplied, the first argument supplied becomes the default file for this session
  - if `arg[1]` is not supplied and no argument is supplied, the file written to is `egged.txt`

- `^C` to close
