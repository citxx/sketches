module Main where

elementAt :: [a] -> Integer -> a
elementAt [] k = error "Invalid arguments"
elementAt (x:_) 1 = x
elementAt (_:t) k = elementAt t (k-1)

main = print (elementAt "abacabadabacaba" 12)
