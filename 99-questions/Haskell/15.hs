module Main where

repli :: [a] -> Int -> [a]
repli l n = repli' l n n
    where
        repli' [] _ _ = []
        repli' (x:xs) 0 n = repli' xs n n
        repli' l@(x:xs) m n = x : repli' l (m-1) n

main = print (repli "abacaba" 3)
