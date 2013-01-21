module Main where

_compress :: (Eq a) => [a] -> a -> [a]
_compress [] x = []
_compress (h:t) x
    | (x==h) = _compress t x
    | otherwise = h:(_compress t h)

compress :: (Eq a) => [a] -> [a]
compress [] = []
compress (h:t) = h:(_compress t h)

main = print (compress "aadbbbbrrkdkfkkkkkkk")
