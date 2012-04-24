
Transfer of ownership- In draw.cpp when I am parsing the string to make a polygon or a Geometry I allocate doubles and Geometry *'s but then after I create the object
										I do not delete them in main. They are not deleted until the destructor for that object, so ownership is transfered to the created Goemetry
										object.
										
										
Chaining to base class- In my Group class when setColor is called, it sets all of its sub objects colors, and also calls the Geometry::setColor, which is chaining to the base class.


Template method- Because I chained to the base class in Group::setColor, I did not use template method, though I could have.


Chain of responsibility - In my setColor, count, translate, area, and perimeter methods of my Group class, each sub-object gets chained responsibility because their versions
										of these functions are called to help calculate the answer.
										
										
Composite	- The group class is a composite class, as it contains several objects from the same family of derived classes.