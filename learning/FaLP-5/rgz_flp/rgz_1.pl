f_read_list(Original_List):-
    writeln("Enter your list"), read(Original_List), is_list(Original_List).

f_doubling_list([],[]).
f_doubling_list([Head | Tail_First], [Head, Head | Tail_Second]):-
    f_doubling_list(Tail_First, Tail_Second).

f_print_list(List):-
    writeln(List).

f_main:-
    f_read_list(Original_List),
    f_doubling_list(Original_List, Doubling_List),
    f_print_list(Original_List),
    f_print_list(Doubling_List).
