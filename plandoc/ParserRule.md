```c++
/*
*   x : i8
*   x : i8 = 10
*   x := 10
*/
auto varDefRule = ParserRule(Groups::VariableDefinition)
    & ParserRule::ID(ID::Identifier)
    | ParserRule::
```