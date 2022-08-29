# Car_sales
This project is a fun terminal simulation of buying cars written in C. It records purchases, the number of cars in stock, customers, time of purchase, and allows customers to have discounts if they have a car dealer membership. 

![image](https://user-images.githubusercontent.com/88378835/187122379-8e3d7d68-cd1f-4f34-b81b-88a28c73a0eb.png)


**Key points**
* No database required! - Once the the program closes (from choosing exit at the menu), it extracts the purchase data, and stores it into a CSV file which it reads from to find pre-existing purchases from customers.
* The maximum sales that the simulation allows is 10, however, this is easily modifiable in the code.
* You can search for specific records (e.g. purchases of a specific quantity)
* There are specific requirements for receiving car club membership
* The simulation checks for incorrect input and does not allow invalid entries


**View Sales menu option:**

<img width="960" alt="image" src="https://user-images.githubusercontent.com/88378835/187123518-8f4178f0-6af4-43c9-94e8-96dcb669f207.png">



**View Cars menu option:**

<img width="374" alt="image" src="https://user-images.githubusercontent.com/88378835/187123638-de7a1b85-3bfe-4684-927e-fd39ad1d74f9.png">


## How to run the simulation
1.Change the CSV file path to your own, the CSV definition is at the top of the page. **there is a forward slash for each sub directory**

<img width="352" alt="image" src="https://user-images.githubusercontent.com/88378835/187122441-154760d7-1c2d-4610-b5d3-4f743961ba5b.png">

2.The code is now ok to run

When you exit from the menu options, you should see this message:

<img width="251" alt="image" src="https://user-images.githubusercontent.com/88378835/187123977-f79c369a-d5ff-4142-a3b9-da0ed53f0dec.png">

This will indicate that the records have successfully been saved to a CSV file - this will not happen if you leave the program any other way.


