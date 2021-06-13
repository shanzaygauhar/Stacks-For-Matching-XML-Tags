# Stacks-For-Matching-XML-Tags
C++ code for matching tags and quotes in XML using struct as a datastructure.
## Execution
Clone the project and run it in Visual Studio. Make sure you keep your xml file in the same project folder and update the file name in the main() to run on your file. This is the piece of code where you add your file name:


![image](https://user-images.githubusercontent.com/68595241/121820885-97515e00-ccae-11eb-9ab5-c08053464de8.png)


## Functionality
The program will get an XML code in an input file and it should figure out if tags and quotes are properly matched or
not using stack. In case the tags are not properly matched the program reports following:
i) the first error,
ii) print the mismatched tag and
iii) inform the line number where the starting tag occurred.

The code handles the following features of XML
1. xml prolog (xml header)
2. xml tags (xml elements). The xml tags are case sensitive.
3. xml attribute
4. xml comments, start with <!-- and ends with -->
