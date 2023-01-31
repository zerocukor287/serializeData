# Simple data serialization example using C++ with only standard library

## When to use
This example serve as an inspiration in case you want to write an array of variable size of structures into a binary file and later read them.
Like a `vector` of `structs` that has `string` members, as follows.  
```
struct Data {
    std::string str;
    int value;
};

std::vector<Data> myCompicatedData;
```

## Usage
Use `ofstream` to write your data then open it with an `ifstream`. Writing and reading depends on the type of the data:
- For binary data (like `double` or `float`) use the [`std::ofstream::write`](https://en.cppreference.com/w/cpp/io/basic_ostream/write) method
- For plain data (like `bool`, `int`, `uint32_t`) use the `operator<<`
- For writing `std::string` use the `operator<<` followed by a delimiter character, and read using the `getline` method

## Constrains
1. You must define a `char` that will be the delimiter, and under no circumstances present in the `string` member
2. Maximum length of one `string` must be defined
3. The `structure` should not end with the `string`

## Consequences
It is not possible to write to binary then read structures only containing `string` members (constraint #3).  
Writing data from raw user input is not recommended as it  
a) might contain the delimiter (constraint #1) 
b) might be 'infinite' long (constraint #2)
therefore invalidating the read.
