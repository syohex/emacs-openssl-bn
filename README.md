# openssl-bn.el

OpenSSL BN binding of Emacs Lisp

## Interfaces

### `(openssl-bn-prime-p "number")`

Check the `number` is prime number. If it is prime number then this function returns `t` otherwise returns `nil`.
First argument is string which looks like integer.
