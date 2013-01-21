module Main where

myReverse :: [a] -> [a]
myReverse [] = []
myReverse (x:t) = (myReverse t) ++ [x]

isPalindrome :: (Eq a) => [a] -> Bool
isPalindrome l = l == (myReverse l)

main = print (isPalindrome "abacabadabacaba")
