# Assignment3

This is the source code repository that will be used as a starting point for Assignment 3. You should edit this file (README.md) in order to write your responses for Question 2.

## Question 2

1.  Starting from `main` in `movie_recommender.c`.
    1. First function called is `load_one_preference`. 

        It's using some global variables such as `MAX_LINES` which are defined in `preferences.h` header file.

       1. Which calls `LOAD_FIELD` which in turn calls the function pointer `input_fcn_array` properly (it chooses the appropriate function to be pointed at). More on this in Q2.3.

    1. If flag `-DDEBUG` was used when running the program, `print_preferences` will then be called
        1. Which calls `PRINT_FILED` which calls the function `output_fcn_array` properly (it chooses the appropriate function to be pointed at).
    
    1. `compute_difference_numeric` and `compute_difference_alphabetic` are then both called.

    1. If `-DDEBU` flag was used, then `print_preference` is called.
    
    1. The movie selection is then printed.

1. `input_fcn_array[filed_number]` is an *array* of function pointers with the number of fields as its size. Each element of this array is a function (`input_string`,`input_double`,...) that's appropriate for each of the fields. 
`LOAD_FIELD` is like a map; when calling it with the `field_number` it points to the "field_number"th element (function) of `input_fcn_array`, which is pre-chosen to be compatible with the field corresponding to `field_number`.

1. The array stores the offset of each field from the *start* of the struct. The structs elements might be stored in a different order than the way they're written (initialized in the struct). So the best way to get the offset of each member of the struct is to use `offsetof` which returns the offset in bytes of each memeber from the beginning of the object to the specified memeber.
