module Main where

myReverse :: [a] -> [a]
myReverse [] = []
myReverse (x:t) = (myReverse t) ++ [x]

main = print (myReverse "Hello, world!!!")
