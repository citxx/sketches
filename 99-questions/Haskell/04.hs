module Main where

myLength :: [a] -> Integer
myLength [] = 0
myLength (_:t) = (myLength t) + 1

main = print (myLength "abacabadabacaba")
