-record(person,{
    id,
    name,
    age,
    gender
    }).

%%Далее следует вывод командной строки%%

Persons=[#person{id = 1, name = "Bob", age = 23, gender = male}, #person{id = 2, name = "Kate", age = 20, gender = female}, #person{id = 3, name = "Jack", age = 34, gender = male}, #person{id = 4, name = "Nata", age = 53, gender = female}].
[#person{id = 1,name = "Bob",age = 23,gender = male},
#person{id = 2,name = "Kate",age = 20,gender = female},
#person{id = 3,name = "Jack",age = 34,gender = male},
#person{id = 4,name = "Nata",age = 53,gender = female}]


[FirstPerson | _] = Persons.
[#person{id = 1,name = "Bob",age = 23,gender = male},
 #person{id = 2,name = "Kate",age = 20,gender = female},
 #person{id = 3,name = "Jack",age = 34,gender = male},
 #person{id = 4,name = "Nata",age = 53,gender = female}]
FirstPerson.
#person{id = 1,name = "Bob",age = 23,gender = male}
%%Присвоенно переменной FirstPerson значение первой персоны, т.к. знак "_" означает игнор. остальные персоны. 

[_, SecondPerson,_,_] = Persons.
SecondPerson.
#person{id = 2,name = "Kate",age = 20,gender = female}
%%Переменной присовено значение второй персоны, так как все остальные игнорируем при помощи "_".

 SecondName = SecondPerson#person.name.
"Kate"
SecondAge = SecondPerson#person.age.
20
[_,#person{name = SecondName, age = SecondAge} |_Rest] = Persons.
[#person{id = 1,name = "Bob",age = 23,gender = male},
 #person{id = 2,name = "Kate",age = 20,gender = female},
 #person{id = 3,name = "Jack",age = 34,gender = male},
 #person{id = 4,name = "Nata",age = 53,gender = female}]
%Переменным присвоены соотвествующие значения из второй персоны (SecondPerson), age = возраст, соотвественно 20, name = имя, соответственно Kate.
Persons.
[#person{id = 1,name = "Bob",age = 23,gender = male},
 #person{id = 2,name = "Kate",age = 20,gender = female},
 #person{id = 3,name = "Jack",age = 34,gender = male},
 #person{id = 4,name = "Nata",age = 53,gender = female}]
%Список Persons не изменился.
SecondPerson#person{age = 21}.
#person{id = 2,name = "Kate",age = 21,gender = female}
Persons.
[#person{id = 1,name = "Bob",age = 23,gender = male},
 #person{id = 2,name = "Kate",age = 20,gender = female},
 #person{id = 3,name = "Jack",age = 34,gender = male},
 #person{id = 4,name = "Nata",age = 53,gender = female}]
%Переменные постоянны согласны "Pattern matching".



 Persons = [#{id => 1, name => "Bob", age => 23, gender => male}, #{id => 2, name => "Kate", age => 20, gender => female}, #{id => 3, name => "Jack", age => 34, gender => male}, #{id => 4, name => "Nata", age => 54, gender => female}].
[#{age => 23,gender => male,id => 1,name => "Bob"},
 #{age => 20,gender => female,id => 2,name => "Kate"},
 #{age => 34,gender => male,id => 3,name => "Jack"},
 #{age => 54,gender => female,id => 4,name => "Nata"}]

 [FirstPerson | _] = Persons.
FirstPerson.
#{age => 23,gender => male,id => 1,name => "Bob"}
%Присвоено значение первой переменной так как остальные ограничили согласно синтаксису "_".(так же они поменяли порядок)

[_,_, #{name := Name, age := Age}, _] = Persons.
Name.
"Jack"
Age.
34
%Перменным Age и Name были присвоены их значения согласно изначальному формату ввода, из чего можно сделать вывод что сортируются пременные только при выводе.

[_First,_Second, #{name := Name, age :=Age}|_Rest] = Persons.
 Name.
"Jack"
 Age.
34
%По большому счету мы сделали тоже самое что и в предидущем пункте, сверили значение переменных согласно паттерн матчингу(по логичке программы), все верно - ошибки нет.
Persons.
[#{age => 23,gender => male,id => 1,name => "Bob"},
 #{age => 20,gender => female,id => 2,name => "Kate"},
 #{age => 34,gender => male,id => 3,name => "Jack"},
 #{age => 54,gender => female,id => 4,name => "Nata"}]

FirstPerson#{age := 24}.
#{age => 24,gender => male,id => 1,name => "Bob"}
17> FirstPerson.
#{age => 23,gender => male,id => 1,name => "Bob"}
%Чтобы изменить возраст, нужно создать новую мапу, переменные постоянны.
 Persons.
[#{age => 23,gender => male,id => 1,name => "Bob"},
 #{age => 20,gender => female,id => 2,name => "Kate"},
 #{age => 34,gender => male,id => 3,name => "Jack"},
 #{age => 54,gender => female,id => 4,name => "Nata"}]

 FirstPerson#{address := "Mira 31"}.
** exception error: bad key: address
     in function  maps:update/3
        called as maps:update(address,"Mira 31",
                              #{age => 23,gender => male,id => 1,
                                name => "Bob"})
        *** argument 3: not a map
     in call from erl_eval:'-expr/6-fun-0-'/2 (erl_eval.erl, line 309)
     in call from lists:foldl/3 (lists.erl, line 1350)
%Если мы хотим ввести новое значение, нужно использовать => т.к. := служит только для обновления существующих.

%Извините что сдал с задержкой, работы очень много.
