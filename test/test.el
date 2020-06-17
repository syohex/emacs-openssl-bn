;;; test.el --- test for openssl-bn.el -*- lexical-binding: t; -*-

;; Copyright (C) 2020 by Shohei YOSHIDA

;; Author: Shohei YOSHIDA <syohex@gmail.com>

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

;;; Code:

(require 'ert)
(require 'openssl-bn)

(ert-deftest prime-p ()
  "Check input is prime number"
  (should-not (openssl-bn-prime-p "1"))
  (should (openssl-bn-prime-p "2"))
  (should-not (openssl-bn-prime-p "4"))
  (should (openssl-bn-prime-p "4776913109852041418248056622882488319"))
  (should (openssl-bn-prime-p "56713727820156410577229101238628035243")))

;;; test.el ends here
