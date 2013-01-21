module Main where

myButLast :: [a] -> a
myButLast [] = error "Invalid argument"
myButLast [x] = error "Invalid argument"
myButLast [x, y] = x
myButLast (_:t) = myButLast(t)

main = print (myButLast "a")
