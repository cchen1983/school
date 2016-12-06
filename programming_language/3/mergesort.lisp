(defconstant data_cnt 20)
(setf temp_arr (make-array '(20)))
(setf data_arr (make-array '(20)))
(defun data_gen (arr) 
    (loop for i from 0 to (- data_cnt 1) do 
        (setf (aref arr i) (random 100))     
    ) 
)   

(data_gen data_arr)
(print "Randmo numbers:")
(print data_arr)

(defun do_merge (left middle right)
    (setf lsub left)
    (setf rsub (+ middle 1))
    (loop for i from left to right do 
        (if (and (<= lsub middle) 
                 (or (> rsub  right)
                     (< (aref data_arr lsub) (aref data_arr rsub)) )
            )
            (progn 
                (setf (aref temp_arr i) (aref data_arr lsub))
                (setf lsub (+ lsub 1))
            )
            (progn
                (setf (aref temp_arr i) (aref data_arr rsub))
                (setf rsub (+ rsub 1))
            )
        )
    )
    (loop for i from left to right do 
        (setf (aref data_arr i) (aref temp_arr i))
        ;(print (aref data_arr i))
    )
)

(defun merge_sort (l r)
    (if (< l r)
        (progn
            (merge_sort l (floor (+ l r) 2))
            (merge_sort (+ (floor (+ l r) 2) 1) r)
            (do_merge l (floor (+ l r) 2) r)
        )
    )
)

(print "Merge Sort:")
(merge_sort 0 (- data_cnt 1))
(print data_arr)
