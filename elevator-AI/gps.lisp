

#| 

    Kevin Xiao and David Roccapriore
    CPSCI375 - Proj4.2
    GPS demonstration - Elevator Controller

    This assignment solves an elevator controller puzzle with the assistance
    of Peter Norvig's GPS code. Elevator controller details are located further down.
    
|#

(load "auxfns.lisp")



;;; -*- Mode: Lisp; Syntax: Common-Lisp; -*-
;;; Code from Paradigms of Artificial Intelligence Programming
;;; Copyright (c) 1991 Peter Norvig

;;;; File gps.lisp: Final version of GPS



;;; ==============================

(defun executing-p (x)
  "Is x of the form: (executing ...) ?"
  (starts-with x 'executing))

(defun starts-with (list x)
  "Is this a list whose first element is x?"
  (and (consp list) (eql (first list) x)))

(defun convert-op (op)
  "Make op conform to the (EXECUTING op) convention."
  (unless (some #'executing-p (op-add-list op))
    (push (list 'executing (op-action op)) (op-add-list op)))
  op)

(defun op (action &key preconds add-list del-list)
  "Make a new operator that obeys the (EXECUTING op) convention."
  (convert-op
    (make-op :action action :preconds preconds
             :add-list add-list :del-list del-list)))

;;; ==============================

;(mapc #'convert-op *school-ops*)

;;; ==============================

(defvar *ops* nil "A list of available operators.")

(defstruct op "An operation"
  (action nil) (preconds nil) (add-list nil) (del-list nil))

(defun GPS (state goals &optional (*ops* *ops*))
  "General Problem Solver: from state, achieve goals using *ops*."
  (remove-if #'atom (achieve-all state goals nil)))

;;; ==============================

(defun achieve-all (state goals goal-stack)
  "Achieve each goal, and make sure they still hold at the end."
  (let ((current-state state))
    (if (and (every #'(lambda (g)
                        (setf current-state
                              (achieve current-state g goal-stack)))
                    goals)
             (subsetp goals current-state :test #'equal))
        current-state)))

(defun achieve (state goal goal-stack)
  "A goal is achieved if it already holds,
  or if there is an appropriate op for it that is applicable."
  (dbg-indent :gps (length goal-stack) "Goal: ~a" goal)
  (cond ((member-equal goal state) state)
        ((member-equal goal goal-stack) nil)
        (t (some #'(lambda (op) (apply-op state goal op goal-stack))
                 (find-all goal *ops* :test #'appropriate-p)))))

;;; ==============================

(defun member-equal (item list)
  (member item list :test #'equal))

;;; ==============================

(defun apply-op (state goal op goal-stack)
  "Return a new, transformed state if op is applicable."
  (dbg-indent :gps (length goal-stack) "Consider: ~a" (op-action op))
  (let ((state2 (achieve-all state (op-preconds op) 
                             (cons goal goal-stack))))
    (unless (null state2)
      ;; Return an updated state
      (dbg-indent :gps (length goal-stack) "Action: ~a" (op-action op))
      (append (remove-if #'(lambda (x) 
                             (member-equal x (op-del-list op)))
                         state2)
              (op-add-list op)))))

(defun appropriate-p (goal op)
  "An op is appropriate to a goal if it is in its add list."
  (member-equal goal (op-add-list op)))

;;; ==============================

;;; ==============================

;;; ==============================

;;; ==============================

(defun GPS (state goals &optional (*ops* *ops*))
  "General Problem Solver: from state, achieve goals using *ops*."
  (find-all-if #'action-p
               (achieve-all state goals nil)))

(defun action-p (x)
  "Is x something that is (start) or (executing ...)?"
  (or (equal x '(start)) (executing-p x)))

;;; ==============================

;;; ==============================


;;; ==============================

(defun achieve-all (state goals goal-stack)
  "Achieve each goal, trying several orderings."
  (some #'(lambda (goals) (achieve-each state goals goal-stack))
        (orderings goals)))

(defparameter *current-state* nil)

(defun achieve-each (state goals goal-stack)
  (setf *current-state* state)
  (if (and (every #'(lambda (g)
		      (setf *current-state*
			    (achieve *current-state* g goal-stack)))
		  goals)
	   (subsetp goals *current-state* :test #'equal))
      *current-state*)
)

(defun orderings (l) 
  (if (> (length l) 1)
      (list l (reverse l))
      (list l)))

;;; ==============================

(defun achieve (state goal goal-stack)
  "A goal is achieved if it already holds,
  or if there is an appropriate op for it that is applicable."
  (dbg-indent :gps (length goal-stack) "Goal: ~a" goal)
  (cond ((member-equal goal state) state)
        ((member-equal goal goal-stack) nil)
        (t (some #'(lambda (op) (apply-op state goal op goal-stack))
                 (appropriate-ops goal state))))) ;***

(defun appropriate-ops (goal state)
  "Return a list of appropriate operators, 
  sorted by the number of unfulfilled preconditions."
  (sort (copy-list (find-all goal *ops* :test #'appropriate-p)) #'<
        :key #'(lambda (op) 
                 (count-if #'(lambda (precond)
                               (not (member-equal precond state)))
                           (op-preconds op)))))

;;; ==============================

;;; ==============================



; ==========================================================================================
; ELEVATOR CONTROLLER - operations setup
;
; The following code will construct a list of possible elevator operations, based on
; the number of floors passed into " (generate-floors x) ". This list will be automatically
; loaded into the " *ops* " variable. Once the gps function is given a initial state and a goal,
; a list of actions/operations for the elevator to accomplish that goal will be generated.
;
; Assumptions:
; - A passenger's origin and destination are never the same.
; - A passenger's origin and destination are within the available floors.
; - A passenger's origin and destination do not change between the initial and goal state.
; 
; ==========================================================================================

(defun eval-dir (a b)
  "Return 'up if b is higher than a. Return 'down if a is higher than b."
  (cond ((< a b) '(up))
	((> a b) '(down))
  )
)

(defun move-elevator-op (a b)
  "Make an operator to move elevator from floor 'a' to floor 'b'."
  (op  `(move from ,a to ,b)
      :preconds `((floor ,a) (closed) ,(eval-dir a b))
      :add-list `((floor ,b))
      :del-list `((floor ,a))
  )
)

(defun up-op ()
  "Make an operator to change elevator direction to 'up."
  (op '(going up)
      :preconds '((down))
      :add-list '((up))
      :del-list '((down))
  )
)

(defun down-op ()
  "Make an operator to change elevator direction to 'down."
  (op '(going down)
      :preconds '((up))
      :add-list '((down))
      :del-list '((up))
  )
)

(defun open-op ()
  "Make an operator to open the elevator door."
  (op '(open door)
      :preconds '((closed))
      :add-list '((open))
      :del-list '((closed))
  )
)

(defun close-op ()
  "Make an operator to close the elevator door."
  (op '(close door)
      :preconds '((open))
      :add-list '((closed))
      :del-list '((open))
  )
) 	

(defun pickup (o d)
  "Make an operator to pick up a passenger on floor o, with destination floor d."
  (op `(pick up passenger going to floor ,d on floor ,o)
      :preconds `((open)(floor ,o)(,o ,d waiting))
      :add-list `((,o ,d in-transit))
      :del-list `((,o ,d waiting))
  )
)

(defun dropoff (o d)
  "Make an operator to drop off a passenger on floor d, who entered on floor o."
  (op `(drop off passenger from floor ,o on floor ,d)
      :preconds `((open)(floor ,d)(,o ,d in-transit))
      :add-list `((,o ,d arrived))
      :del-list `((,o ,d in-transit))
  )
)

(defun generate-floors (x)
  "Generate all elevator operations and load them into *ops*, including every
   combination of floor pairings."
  (setf *ops* nil)
  (setf *ops* (append *ops* (list (up-op) (down-op) (close-op) (open-op))))
  (setf *ops* (append *ops* (gen-floors-move x #'move-elevator-op)))
  (setf *ops* (append *ops* (gen-floors x #'pickup)))
  (setf *ops* (append *ops* (gen-floors x #'dropoff)))

)


(defun numbers (n)
  "Generates a list of numbers from 1 to n. E.g. (numbers 5) returns (1 2 3 4 5)"
   (loop for i from 1 upto n collect i)
)

(defun remove-nil (ops)
  "Removes nil elements in a list."
  (cond ((null ops) nil)
	((equal nil (first ops)) (remove-nil (rest ops)))
	(T (cons (first ops) (remove-nil (rest ops))))
  )
)

(defun flatten-helper (x y)
  "Helper function to flatten function."
  (if (equal nil (first y))
      (if (listp x) 
	  (flatten-helper (first x) (rest x)) 
	  (list x)
      )
      (if (listp x)
	  (append (flatten-helper (first x) (rest x)) (flatten-helper (first y) (rest y)))
	  (append (list x) (flatten-helper (first y) (rest y)))
      )
  )
)

(defun flatten (x)
  "Removes all instances of nested lists in a list."
  (flatten-helper (first x) (rest x))
)

(defun gen-floors (x o)
  "Generates all combinations of floor pairings for floor-related functions."
  (flatten (loop for i in (numbers x) collect (gen-floors-helper i x o)))
)

(defun gen-floors-helper (i x o)
  "Helper function to gen-floors function."
  (remove-nil (loop for j in (numbers x) collect (cond ((not (equal i j)) (apply o `(,i ,j))))))
)

(defun gen-floors-move (x o)
  (flatten (loop for i in (numbers (- x 1)) collect (list (apply o `(,i ,(+ i 1))) (apply o `(,(+ i 1) ,i)))))
)
  

; ==========================================================================================
; ELEVATOR CONTROLLER - task divider
;
; To optimize the performance of GPS with this elevator controller, the overall goal-state
; needs to be broken down into multiple simpler goal-states. Calling GPS on each of these
; smaller goal-states, with subsequent calls inheriting the final states of previous calls,
; should produce a far more efficient solution to the overall goal-state.
;
; The following functions divide the overall goal-state into 'pickup' and 'dropoff' phases.
; Given a passenger manifest (i.e. the start state), it will first call GPS on some 'pickup'
; objectives. The final state of that call is inherited as the starting state of a second GPS
; call on some 'dropoff' objectives. The final state of the second GPS call is passed to a
; third GPS call on another set of 'pickup' objectives and so on.
;
; The elevator will alternate between these two phases until it reaches a state where
; all passengers have been delivered, or until the GPS is unable to deduce a solution. 
; While the gps has no concept of time, it is easier to describe the task division 
; process from a chronological perspective...
;
; The pickup phase will continuously pick up passengers until the elevator recognizes that
; one of the passengers it picked up needs to be dropped off. The dropoff phase will
; continuously drop off passengers until the elevator recognizes that there are passengers
; that need to be picked up ahead.
;
; Both phases will ignore passengers that do not share a direction with the elevator: if
; the elevator is going up, it will not pick up passengers who wish to go down, nor will 
; passengers awaiting pickup be considered in deciding when the dropoff phase ends.
;
; The elevator will change direction if there are no longer any servicable passengers
; on-board and/or ahead. 
;
;
; ==========================================================================================


(defun newlist (mylist)
  ; Creates a second copy of the passenger manifest,
  ; to avoid unwanted synchronization between lists.
  ; Only effective for one use.
  (defparameter returnlist nil)
  (dolist (p mylist)
    (cond ((equal (third p) 'waiting) (setf returnlist (append returnlist `((,(first p) ,(second p) waiting)))))
	  ((equal (third p) 'in-transit) (setf returnlist (append returnlist `((,(first p) ,(second p) in-transit)))))
	  ((equal (third p) 'arrived) (setf returnlist (append returnlist `((,(first p) ,(second p) arrived)))))
    )
  )
  returnlist
)


(defun generate (p f s)
  ; Initializes parameters and calls function to generate GPS ops.
  ; Also initializes the pickup phase.
  (defparameter micro-op nil)
  (defparameter lim nil)
  (defparameter p-state nil)
  (defparameter max f)

  (generate-floors f)
  (gps (append s (newlist p)) '())
  (setf p-state p)
  (pickup-phase (second s))
)


(defun pickup-phase (direction)
  ; For all passengers travelling in the same direction as the elevator,
  ; mark them for pickup. Skip said passengers who are too far to be picked
  ; up before somebody needs to be dropped off.
  (if (equal '(up) direction)
      (setf lim max)
      (setf lim 1)
  )
  (let ((o #'<))
    (if (equal '(down) direction)
	(setf o #'>)
    )
    (apply-pickup direction o) ; Creates the mini-goal-state according 
			       ; to the aforementioned description.
  )
  (if (equal micro-op nil)
      ; Change direction if there is nothing left ahead.
      ; Also check if overall-goal-state has been reached,
      ; end the procedure if true.
      (if (job-done)
	  (wrap-up)
	  (if (equal '(up) direction) (pickup-phase '(down)) (pickup-phase '(up)))
      )
      (list (gps *current-state* micro-op) (dropoff-phase direction))
  )
  
)

(defun apply-pickup (direction o)
  ; see above
  (setf micro-op nil)
  (dolist (p p-state)
    (if (and (equal (eval-dir (first p) (second p)) direction) (equal (third p) 'waiting))
	(list (setf micro-op (append micro-op (list p)))
	      (if (apply o `(,(second p) ,lim)) (setf lim (second p)))
	)
    )
  )
  (dolist (p micro-op)   
    (if (apply o `(,lim ,(first p)))
	(setf micro-op (delete p micro-op))
        (setf (third p) 'in-transit)      
    )
  )
  (sort-micro-op #'first o)
)

(defun dropoff-phase (direction)
  ; For all passengers on the elevator, mark them for dropoff. 
  ; Skip passengers who have destinations further away than the
  ; nearest passenger qualified for pickup. 
  (if (equal '(up) direction)
      (setf lim max)
      (setf lim 1)
  )
  (let ((o #'<))
    (if (equal '(down) direction)
	(setf o #'>)
    )
    (apply-dropoff direction o) ; Creates the mini-goal-state according to
			      	; the aforementioned descriptions.
  )
  (if (equal micro-op nil)
      ; Change direction is there is nothing left ahead.
      (if (equal '(up) direction) (pickup-phase '(down)) (pickup-phase '(up)))
      (list (gps *current-state* micro-op) (pickup-phase direction))
  )
)

(defun apply-dropoff (direction o)
  ; see above
  (setf micro-op nil)
  (dolist (p p-state)
    (if (and (equal (eval-dir (first p) (second p)) direction) (equal (third p) 'waiting))
	(if (apply o `(,(first p) ,lim)) (setf lim (first p)))
    )
  )
  (dolist (p p-state)
    (if (equal (third p) 'in-transit)
	(if (or (equal (second p) lim)(apply o `(,(second p) ,lim))) (setf micro-op (append micro-op (list p))))
    )
  )
  (dolist (p micro-op)
    (setf (third p) 'arrived)
  )
  (sort-micro-op #'second o)
)



(defun job-done ()
  ; Checks if overall-goal-state (all passengers arrived) has been reached.
  (defparameter result t)
  (dolist (p p-state)
    (if (equal (third p) 'waiting) (setf result nil))
  )
  result
)

(defun sort-micro-op (column o)
  ; Sorts ordering of mini-goal-states since GPS is sensitive to the
  ; order of the conditions that constitute a goal-state.
  (defparameter order nil)
  (defparameter temp nil)
  (dolist (p micro-op)
    (setf order (append order (list (apply column (list p)))))
  )
  (sort order o)
  (dolist (n order)
    (dolist (p micro-op)
      (if (equal (apply column (list p)) n)
	  (setf temp (append temp (list p) ))
      )
    )
  )
  (setf micro-op temp)
)

(defun wrap-up ()
  ; Called when goal-state has been reached. Prints out the plan 
  ; deduced by GPS and prints further instructions for the user.
  (format t "~%=========================================================================================================~%" #\newline)
  (print *current-state*)
  (format t "~%~%Job complete! ~%" #\newline)
  (instructions)
  (format t "~%=========================================================================================================~%" #\newline)

)


(defun instructions ()
  ; Prints instructions for using the program.
  (format t "~%   Type '(check-parameters)' to view current parameters for the elevator controller.~%" #\newline)
  (format t "~%   Type '(start)' to run the elevator controller.~%" #\newline)
  (format t "~%   Type '(edit-floors x)' to change the number of floors to value 'x'.~%" #\newline)
  (format t "      e.g.  (edit-floors 10)~%" #\newline)
  (format t "~%   Type '(edit-passengers x)', with 'x' being the list of passengers you would like to handle.~%" #\newline)
  (format t "      Passenger info syntax: (origin destination status)~%" #\newline)
  (format t "      e.g.  (edit-passengers '((1 5 in-transit) (9 4 waiting) (3 7 waiting) (8 6 waiting) (2 4 arrived)) )~%" #\newline)
  (format t "~%   Type '(edit-start-state x)', with 'x' being the desired starting parameters for the elevator.~%" #\newline)
  (format t "      Start info syntax: ((START) (direction) (current floor) (door status))~%" #\newline)
  (format t "      e.g.  (edit-start-state '((START) (up) (floor 1) (open)) )~%" #\newline)
  (format t "      e.g.  (edit-start-state '((START) (down) (floor 10) (closed)) )~%" #\newline)
  (format t "~%   Type '(reset)' to reload default parameters.~%" #\newline)
  T
)

(defparameter floors nil)
(defparameter passengers nil)
(defparameter start-state nil)

(defun main ()
  ; Called when the program is initially loaded. Establishes default
  ; parameters and prints instructions for the user.
  (setf floors 10)
  (setf passengers '((1 5 in-transit) (9 4 waiting) (3 7 waiting) (8 6 waiting) (2 4 arrived)) )
  (setf start-state '((START) (up) (floor 1) (open)) )


  (format t "~%=========================================================================================================~%" #\newline)
  (format t "~%Welcome to the General Problem Solver demonstration, elevator controller edition!~%" #\newline)
  (instructions)
  (format t "~%=========================================================================================================~%" #\newline)
  T
)

(defun edit-floors (x)
  ; Parameter access - allows user to edit number of floors.
  (setf floors x)
  T
)

(defun edit-passengers (x)
  ; Parameter access - allows user to edit passenger manifest.
  (setf passengers x)
  T
)

(defun edit-start-state (x)
  ; Parameter access - allows user to edit initial state of the elevator.
  (setf start-state x)
  T
)

(defun check-parameters ()
  ; Allows user to view current parameters.
  (format t "~%=========================================================================================================~%" #\newline)
  (format t "~%(floors " #\newline)
  (princ floors)
  (format t ")~%"  #\newline)
  (format t "(passengers '")
  (princ passengers)
  (format t " )~%"  #\newline)
  (format t "(start-state '")
  (princ start-state)
  (format t " )~%"  #\newline)
  (instructions)
  (format t "~%=========================================================================================================~%" #\newline)
  T
)

(defun start ()
  ; Runs elevator controller program on current parameters.
  ; Also prints current parameters for easier review of performance.
  (format t "~%=========================================================================================================~%" #\newline)
  (format t "~%(floors " #\newline)
  (princ floors)
  (format t ")~%"  #\newline)
  (format t "(passengers '")
  (princ passengers)
  (format t " )~%"  #\newline)
  (format t "(start-state '")
  (princ start-state)
  (format t " )~%"  #\newline)
  (generate passengers floors start-state)
  T
)


(main)

(defun reset ()
  ; Reloads lisp file to reset default parameters.
  (load "gps.lisp")
)
