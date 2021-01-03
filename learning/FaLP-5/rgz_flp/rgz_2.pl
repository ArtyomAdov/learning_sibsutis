f_split_line(Line, List):-
    split_string(Line, ' ',  ' \t\n', List).

f_generate_format_line([_], Line):-
    Line = '~w~40|~n', !.

f_generate_format_line([_ | Tail], Line_First):-
    f_generate_format_line(Tail, Line_Second),
    string_concat('~w~t' ,Line_Second, Line_First).

f_file(InF):-
    at_end_of_stream, !;
    read_line_to_codes(InF, Codes),
    string_chars(Line, Codes),
    f_split_line(Line, List),
    f_generate_format_line(List, Format_Line),
    format(Format_Line, List),
    f_file(InF).

f_main(In, Out):-
    see(In),
    tell(Out),
    telling(_),
    seeing(InF),
    f_file(InF),
    seen,
    told.
