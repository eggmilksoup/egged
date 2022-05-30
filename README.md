egged, the egg editor
=====================
like `ed` but less useful:

- two modes: insert and command

- six commands:
  - (a)ppend
  - repla(c)e
  - (d)elete
  - (p)rint
  - (q)uit
  - (w)rite

- buffered with a temp file

- (a) takes a single address, (c), (d), and (p) take ranges

- the default address for (c), (d), and (p) is the entire document, and the default address for (a) is the end of the file

- (w) takes one or zero arguments:
  - if `arg[1]` is supplied, no arguments writes to that file
  - if `arg[1]` is not supplied, the first argument supplied becomes the default file for this session
