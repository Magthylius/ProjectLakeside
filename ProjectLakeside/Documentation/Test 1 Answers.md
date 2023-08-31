From my understanding, I will assume that these functions are written in a UCLASS.

# PrintArray's parameter 
**PrintArray** takes a copy parameter instead of a reference parameter, which will create a copy of the whole array instead.
It is not efficient considering that the usage of the function is to read information from given arrays only.
An improvement of the reference parameter is to also append a const prefix, to ensure the parameter object is not modified during the print.
The better parameter will be *const TArray<AActor*>& Array* instead.

# AActor pointer
It would be wiser to use smart pointers to handle pointers to avoid memory leaks in the program.
If the class owns the actors, it would use *TObjectPtr<AActor>*; and if not, use *TWeakObjectPtr<AActor>*, with garbage collection in mind.

# PrintArray's for loop
The auto keyword might not be suitable, as it is current copying the pointer (which leads to the same object), and can be improved with *auto&* which takes the pointer from the array as a reference instead. For safety, the actor element should be checked for its validity before printing, else it might cause a crash.

# PopulateArray's parameter
Parameter is not modified and can use a *const* prefix to show its immutability. Personally, I would prefer to follow Unreal Engine's conventions and also name parameters more distinctly to avoid collaboration issues.
I would change it to *const int ActorCount* instead.
