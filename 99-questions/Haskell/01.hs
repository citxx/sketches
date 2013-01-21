module Main where

myLast :: [a] -> a
myLast [] = error "Invaled value of argument"
myLast [x] = x;
myLast (_:t) = myLast t

main = print (myLast "")
