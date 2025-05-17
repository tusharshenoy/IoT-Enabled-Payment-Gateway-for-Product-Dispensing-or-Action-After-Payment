# IoT-Enabled-Payment-Gateway-for-Product-Dispensing-or-Action-After-Payment
### 📋 **1. Introduction**

The Internet of Things (IoT) connects physical devices like sensors, processors, and electronic components to the internet, enabling them to communicate and share data seamlessly. Since its early days, from the first internet-connected Coca-Cola machine in 1982 to the widespread use of smart home devices today, IoT has transformed industries like healthcare, agriculture, and transportation.

**Payment Gateways** are critical for secure, cashless transactions, acting as intermediaries between customers and merchants. They securely transmit sensitive payment data, enabling digital payments through credit/debit cards, UPI, and digital wallets. Examples include PayPal, Stripe, and Razorpay.

**Vending Machines** have also evolved from simple coin-operated devices to smart systems that accept digital payments and use IoT for real-time monitoring. However, many traditional machines still rely on cash or card payments, lacking real-time inventory tracking and secure, automated payment options. This project addresses these gaps by integrating IoT and secure, UPI-based payments to create a seamless, cashless vending experience.

### **Aim**

To design and develop an IoT-enabled payment gateway system using a low-cost microcontroller, supporting UPI-based transactions for automated product dispensing or service activation.

### **Objectives**

1. Develop a secure, UPI-based payment gateway on an IoT-enabled ESP32 microcontroller.
2. Integrate real-time transaction tracking using Google Firebase.
3. Eliminate the need for physical currency or OS-based devices.
4. Offer versatile applications beyond conventional vending systems.

### **Problem Formulation**

Traditional payment systems rely heavily on cash or OS-based devices, leading to inefficiencies and security challenges. This project aims to develop a low-cost IoT-based payment gateway supporting real-time, secure, UPI transactions without the need for additional apps or OS devices, enhancing convenience and reducing operational costs.

### **Proposed Method**

The system consists of:

1. **ESP32 Microcontroller** - Processes user inputs and manages transactions.
2. **Google Firebase** - Real-time database for transaction tracking.
3. **Razorpay** - UPI-based payment gateway with real-time transaction notifications via webhooks.
4. **User Interface** - TFT display and push buttons for product selection and payment confirmation.

### **Methodology**

The system follows a structured approach:

* **Component Selection:** Identifying and integrating essential components like ESP32, Firebase, and Razorpay.
* **Microcontroller Programming:** Setting up the ESP32 for transaction verification and dispensing control.
* **Firebase Integration:** Real-time data storage for transaction status.
* **Razorpay Setup:** Secure, UPI-based payments using dynamic QR codes.
* **Final Deployment:** Testing and optimizing the system for real-world conditions.

### 📋 **2. System Block Diagram**

#### **Figure 2.1 Block Diagram**
![blockdiagram](https://github.com/user-attachments/assets/9d93b81c-ad1b-4b13-8a61-4f4aaf92fce7)



Figure 2.1 illustrates an IoT-enabled payment gateway system designed for a product vending or action-triggering device, such as a vending machine. At the core of this system lies the IoT microcontroller, which manages various components through its GPIO pins. The microcontroller interfaces with the user, a display unit, and a dispensing mechanism.

When a user interacts with the system, typically through buttons or other input devices, this triggers a series of events beginning with the display of a QR code on the display unit. The QR code serves as a prompt for the user to scan it using a mobile device, initiating the payment process.

The payment gateway, a crucial part of this setup, manages the transaction, ensuring that the payment is secure and verified. Once the user completes the payment, the gateway communicates the transaction details to a cloud platform. This platform acts as a bridge, storing the payment information and sending updates to the IoT microcontroller. The communication between the cloud platform and the microcontroller occurs over the internet, facilitated by an Internet Service Provider (ISP) that ensures real-time connectivity.

Upon receiving confirmation of successful payment from the cloud platform, the IoT microcontroller activates the dispensing mechanism, releasing the selected product or triggering a specified action. If the payment fails, the system will remain inactive for a certain period, giving the user time to attempt the payment again. During this waiting period, no product will be dispensed, and the display will not show any feedback. If the payment is not successfully processed within the specified time frame, the system will reset, returning to its initial state and awaiting further input from the user. This ensures that the process remains secure, automated, and the system is ready for a new transaction attempt.


#### **2.2 Specification of Major Equipment**

In this project, the major equipment includes the ESP32 Wroom 32 microcontroller, which serves as the core of the system, managing secure communication and transaction processing. The ESP32’s capabilities enable it to continuously monitor Firebase for real-time payment updates and to interface seamlessly with the dispensing mechanism upon transaction confirmation.

#### **Figure 2.2 ESP32 Wroom 32**
![esp](https://github.com/user-attachments/assets/606f3b67-95ec-4693-a853-16f220e3e9b4)



**ESP32 Wroom 32 Features:**

* **Wi-Fi Capabilities:** Seamless communication with Firebase for real-time updates.
* **Flexible Network Modes:** Supports AP, STA, and AP+STA for reliable connectivity.
* **Processing Power:** Dual CPU cores with adjustable clock frequencies.
* **Memory:** 448 KB of ROM, 520 KB of SRAM, and 4 MB of SPI flash storage.
* **Peripherals:** UART, SPI, I2C, and PWM for easy hardware integration.
* **Power Efficiency:** Operates at 3.3V with an average current of 80 mA.
* **Temperature Range:** -40 to 85°C, suitable for various environments.

This makes the ESP32 ideal for secure, automated payment systems, coordinating user interactions with Firebase and Razorpay for real-time, reliable transaction management.


#### **Firebase as the Real-Time Database**

Firebase acts as a cloud-based, real-time database that securely stores transaction data and updates the payment status after processing through Razorpay. This integration with the ESP32 allows for instant transaction verification, enabling timely product dispensing or service activation upon payment confirmation. Firebase’s real-time updates ensure seamless, continuous communication between the IoT device and the payment gateway, supporting efficient transaction processing.

#### **Figure 2.3: Database URL**
![api](https://github.com/user-attachments/assets/961ff631-efc4-4d4d-8765-843b1568c710)


#### **Figure 2.4: Realtime Database**
![realtime database](https://github.com/user-attachments/assets/9721bf0e-fbf0-4df7-9279-94a8b3ed0aa1)

#### **Figure 2.5: Web API keys and others**
![web api keys and others](https://github.com/user-attachments/assets/de646c30-cdd4-48a7-b938-11b267d0bce2)



**Key Features of Firebase in this Project:**

* **Real-time Data Sync:** Instant transaction updates for fast payment verification.
* **Secure Data Storage:** Prevents unauthorized access and ensures data integrity.
* **Cloud Integration:** Supports real-time communication between the ESP32 and Razorpay.


#### **Razorpay as the Payment Gateway**

Razorpay is a secure fintech platform providing streamlined payment solutions. It supports UPI, credit/debit cards, and net banking, facilitating secure, cashless payments through QR codes for user transactions. The platform verifies transactions and communicates the payment status to Firebase, allowing the ESP32 to confirm the payment status instantly.

**Key Features of Razorpay in this Project:**

* **Secure Transactions:** Handles sensitive payment data securely.
* **Webhook Support:** Real-time transaction notifications to Firebase.
* **Dynamic QR Codes:** Preloaded for quick access, supporting various payment amounts.

#### **2.3 Purpose of Interconnections**

The purpose of the interconnections in this system is to ensure seamless communication and coordination between all components, enabling the system to function as an integrated unit.

* **User Inputs:** Push buttons allow product selection and payment confirmation.
* **QR Code Display:** The ESP32 displays the dynamic QR code for payment, which users scan using mobile payment options like UPI.
* **Data Transfer:** Razorpay sends transaction data to Firebase using webhooks, providing real-time transaction updates.
* **Dispensing Mechanism:** Upon successful payment, the ESP32 triggers the dispensing mechanism to release the selected product.

These interconnections ensure smooth operation by allowing the system to respond efficiently to user actions and payment statuses, guaranteeing secure product dispensing after payment verification.

### 📋 **3. Schematic Circuit Connection**

#### Connection Diagram Setup

#### **Figure 3.1: Circuit Diagram**  
![circuit_image](https://github.com/user-attachments/assets/c2dc9929-0337-4165-ab12-276255cd699d)


The circuit diagram as shown in figure 3.1 depicts a setup featuring an ESP32 microcontroller as the central control unit. The ESP32 is connected to a relay module, a TFT display, push-button switches, a buzzer and multiple motors. Operating as the control hub, the ESP32 receives input from push-buttons connected to its GPIO pins via resistors, which send specific commands, such as activating the motors or triggering other actions.  
The relay module, controlled by the ESP32’s GPIO pins, powers and operates the motors connected to its output channels. Each motor is linked to a dedicated relay channel, allowing independent operation. The relays receive power from an   
external 12V power supply, stepped down to 5V through a buck converter, ensuring proper current requirements for the motors and relays. This 5V output also powers the ESP32 through its VIN pin, with a common ground shared across all components.  
For user interaction, the ESP32 connects to an ILI9341 TFT display via SPI communication (using pins D15, D4, D22, D23, D18 and D19 for CS, RESET, D/C, SD (MOSI), SCK and SDO (MISO) respectively, enabling real-time feedback and displaying motor status and relay activity. Additional visual and audio feedback is provided by a buzzer linked to GPIO pin D13. The 4-channel relay module’s IN1 through IN4 pins connect to GPIO pins TX2, RX2, D12 and D14 on the ESP32, controlling external devices or motors connected to the relay’s output.  
Push-buttons are connected to GPIO pins D27, D26, D25, D33, D32, D35, D34 and VN on the ESP32, with each input pin connected to a 3.3V source, allowing the ESP32 to read user commands. The buzzer and display are powered by 3.3V, with ground shared among all components. The motors connect to the relays through the relays’ COM and N.O. (Normally Open) pins, with each motor’s pin 2 connected to the relay COM pin and grounded through the N.O. pin. This configuration enables the ESP32 to activate relays and complete the motor circuit from a 12V power source connected to motor pin 1.  
In this setup, the ESP32 microcontroller manages the whole system, making it easy to control the motors and relays. The TFT display shows information and the buzzer provides sound feedback to the user. The buck converter makes sure the correct voltage is supplied to all parts of the circuit, allowing smooth control over motor functions and with this arrangement, the ESP32 can handle different components, including push-buttons, the buzzer, the display and relays for motor control. The buck converter helps maintain the right voltage across the system, ensuring everything operates correctly.

#### 3.2 Arduino Libraries used:

In this project, various libraries provide essential functionality for interfacing with external components, managing files, communicating over Wi-Fi and integrating with Firebase.

1. **SPI Communication:** The SPI.h library enables Serial Peripheral Interface (SPI) communication, which is crucial for connecting to SPI-based peripherals. In this setup, it establishes a connection between the Arduino board and the SD card or TFT display, allowing smooth data exchange between components over the SPI interface.   
2. **File System Management:** Using the FS.h library, the project manages file operations like reading and writing data to storage devices, such as SD cards or internal flash memory. This standardized interface simplifies file handling across different hardware setups, ensuring compatibility and ease of use for interacting with files on storage devices.  
3. **SD Card Integration:** The SD.h library provides advanced capabilities to interact with SD cards, which store images or data files for this project. Through this library, files can be created, read and written to the SD card, allowing data logging and retrieval. It also enables navigation through directory structures, making it possible to organize and access multiple files effectively.  
4. **Image Decoding:** The JPEGDecoder.h library allows for decoding JPEG images from SD card files, SPIFFS or byte arrays. This feature is essential when the project needs to display images on the TFT display, as it enables JPEG files to be converted into pixel data for visualization. The library supports various architectures, ensuring compatibility with the Arduino boards used in this project  
5. **TFT Display Control:** The TFTeSPI.h library provides a powerful interface to manage TFT display functionality. It supports displays with SPI or parallel interfaces and includes functions for drawing text, shapes and images on the screen. This library optimizes the visual output of the system, facilitating a user-friendly display for monitoring information, status updates or images in real-time.  
6. **Wi-Fi Connectivity:** The WiFi.h library handles the Wi-Fi connection, enabling the board to connect to local networks or the internet. Through this library, the system can operate as a server or client, enabling data transmission over Wi-Fi. It supports secure connections using various encryption methods and provides IP management, ensuring stable network access for the device.  
7. **Firebase Integration:** The FirebaseESPClient.h library is pivotal for connecting the project to Firebase services. With this library, the device can interact with Firebase’s Realtime Database, Cloud Firestore, Firebase Storage and Cloud Functions. This integration allows real-time data synchronization between the device and the Firebase backend, making it possible to store and retrieve data, send notifications and execute cloud functions. This functionality is essential for projects requiring remote monitoring, data logging or user notifications via Firebase services.  


#### 3.3 Functioning of APIs

The IoT Enabled Payment Gateway System code incorporates various functions from the TFT_eSPI, WiFi and Firebase_ESP_Client libraries to enable its core functionalities. TFT functions are utilized to create a visually appealing and user friendly interface on the display. The user-defined functions and library functions provide a structured approach to managing product dispensing and payment in the system. The runMotorForProduct() function iterates over available products, controlling each relay to dispense the specified quantity based on the selected amount, ensuring precise control over the motors connected to each product. updateStock() adjusts stock levels post-transaction, preventing negative values and maintaining an accurate inventory. The utility function totalSelectedProducts() sums up the quantities selected, allowing verification before advancing to the payment stage. To enhance user interaction, the beep() function briefly activates a buzzer, signaling actions like button presses or errors for immediate feedback. For displaying QR codes on the screen, jpegRender(int xpos, int ypos) uses the JPEGDecoder library to decode and draw images at given coordinates, while drawSdJpeg(const char *filename, int xpos, int ypos) opens JPEG files from the SD card and renders them, displaying error messages if issues arise. The drawHeader() function initializes the screen interface by drawing a header, setting text properties and providing system identification.  
The library functions support key operations. SPI.h manages data exchange via Serial Peripheral Interface (SPI), essential for interactions with the SD card and TFT display. FS.h and SD.h handle SD card operations, using SD.begin() to initialize and SD.open() to open files for reading or writing, such as retrieving QR code images. WiFi.h connects the ESP32 to a Wi-Fi network using WiFi.begin() with network credentials and WiFi.status() to check connectivity, enabling communication with Firebase. For Firebase integration, Firebase.h includes functions like Firebase.signUp() to register the device, Firebase.RTDB.beginStream() to start real-time data streaming and Firebase.RTDB.setStreamCallback() to handle payment status updates and timeouts. JPEGDecoder.h decodes JPEG images, with JpegDec.decodeSdFile() for SD card files and JpegDec.read() for reading image data, essential for QR code display. Finally, TFT_eSPI.h controls the TFT display, using functions like tft.init(), tft.fillScreen(), tft.setTextColor(), tft.setCursor() and tft.print() for setting up the interface, displaying product details, quantities, prices and messages, creating a user-friendly interface for the system.

Here is the cleaned-up version with the requested part removed (*Department of Electronics & Communication Engineering* and the "CHAPTER 3. SCHEMATIC CIRCUIT CONNECTION" line removed). The rest is kept exactly as you asked:


### 📋**4. Results and Discussions**

#### **4.1 Experimental Setup:**
![bread_board](https://github.com/user-attachments/assets/45c793ae-382f-4a11-bc53-68f199c89a47)


The experimental setup for the project is as shown in figure 4.1. The breadboard was used to connect and test various components such as the ESP32 microcontroller, push buttons, buzzer, TFT display and product dispensing mechanism before finalizing the design for the vending machine. It was essential for prototyping the system and ensuring the integration of all components as well as testing their functionality before soldering them onto a permanent circuit board. The setup provided valuable insights about wiring, component interaction and debugging.
Figure 4.1: Experimental Setup

#### **4.2 Vending Machine Setup:**

Along with the electronic components, the vending machine structure was built from MDF board, designed using Fusion 360 and cut with a laser cutter for accuracy. This custom-made machine can hold and dispense up to four products showing the practical use of the developed IoT-based payment gateway system. The internal setup of the vending machine as shown in figure 4.2 depicts the layout of the dispensing mechanism. It features coiled springs placed in individual compartments, each designed to hold a different product. This arrangement enables organised storage and smooth dispensing, as the coiled springs help push products forward when activated, ensuring each item can be dispensed accurately. Figure 4.3 displays the machine’s design as planned in Fusion 360 before adding electronics. It shows an interior view of the vending machine’s framework without products or electronic components. The machine features designated compartments with coiled spirals for product dispensing, arranged to support organised storage and smooth product release. The setup ensures each product can be dispensed independently, highlighting the machine’s mechanical aspects.


#### **Figure 4.2: Inner View**
![ms2](https://github.com/user-attachments/assets/891154c8-862e-48a6-8081-543d11158485)



#### **Figure 4.3: Basic Design**
![ms1](https://github.com/user-attachments/assets/99237d35-bd40-4269-b264-0be525fc28f5)


The figure 4.4 shows the fully assembled vending machine with products in place, demonstrating the complete setup. Four distinct product slots are visible, each stocked with different food items. To the right, there’s a TFT display and a control panel with labeled push buttons. The display shows the GUI, including options for product selection and controls for operating the vending machine, such as increment and decrement buttons and options to proceed or cancel. This setup illustrates the integration of electronic components with the machine’s dispensing mechanism, creating an interactive vending experience.


#### **Figure 4.4: Complete setup**
![vendingmachine1](https://github.com/user-attachments/assets/ab160397-b351-4a5a-bef7-fd63a4276bf6)



#### **Figure 4.5: TFT GUI and Push Buttons**
![TFT_GUI_Push](https://github.com/user-attachments/assets/42c34518-12bf-49be-a79d-6ad24061f523)



#### **Figure 4.6: Dynamic QR code**
![QR](https://github.com/user-attachments/assets/df11dad0-d75a-48ca-b097-d7423889e2ed)



The setup also includes a TFT display interface with easy-to-use buttons and displays like the QR code for payments, product options and navigation buttons for selection as shown in figure 4.5. The images of the TFT display show how users interact with the vending machine, including scanning the QR code to make payments as shown in figure 4.6.

#### 4.3 Successful Integration of the Components
In the development of a payment gateway on an IoT-enabled device for product dispensing or unlocking a service after payment, the ESP32 microcontroller plays a central role in managing and controlling the entire process. The setup of the ESP32 was carefully planned and implemented to ensure smooth operation across multiple components. Here’s a breakdown of how the ESP32 was set up:

1. Hardware Configuration:
   The ESP32 is equipped with built-in Wi-Fi, making it ideal for IoT-based applications. It was connected to peripheral components like the TFT Display, push buttons, buzzer, and the product dispensing mechanism. The GPIO (General Purpose Input/Output) pins of the ESP32 were mapped to control each of these components. For example, specific pins were designated for reading input from the push buttons, triggering the product dispensing mechanism and driving the buzzer.

2. Wi-Fi Setup:
   Since the ESP32 needed to communicate with Google Firebase, establishing a stable Wi-Fi connection was a priority. The Wi-Fi libraries in the ESP32’s firmware were configured to connect to a secure network, allowing it to interact with the cloud-based Firebase database in real-time. This was achieved through simple Wi-Fi commands that enabled the ESP32 to send and receive data over the internet.

3. Firmware Development:
   The ESP32 was programmed using the Arduino IDE, with custom firmware developed to handle various tasks. This firmware was responsible for:
   • Reading user inputs from the push buttons.
   • Displaying the selected product and QR code on the TFT screen.
   • Establishing communication with Firebase for real-time payment verification using Razorpay as the main payment gateway.
   • Utilising Razorpay’s webhook feature to send payment information to Firebase, where it is stored and monitored by the ESP32.
   • Triggering the product dispensing mechanism once the payment is confirmed as successful.
   • Providing audio feedback via the buzzer.

The code was structured to handle these tasks concurrently without interference, ensuring the system could process actions in real-time.

4. Cloud Communication:
   The ESP32’s firmware was integrated with Firebase using the Firebase ESP32 library, which enabled real-time synchronization of data such as transaction status and user actions. The ESP32 monitors the payment information from Firebase; if the payment is successful, it triggers the product dispensing action. If the payment fails, no action is taken.

5. Testing and Debugging:
   During the setup phase, the ESP32 was repeatedly tested to ensure reliable communication with both Firebase and Razorpay. Debugging tools in the Arduino IDE, along with serial print statements were employed to monitor data flow and troubleshoot any issues in communication or logic.

#### 4.4 Cashless Transaction Via Razorpay
The integration of Razorpay as the payment gateway enables the system to process secure, cashless transactions. Users are provided with a dynamic QR code on the TFT screen, linked to their selected product and payment amount. This QR code is scanned via mobile devices using UPI, simplifying the payment process. Once the payment is initiated, Razorpay ensures the transaction is securely processed, eliminating the need for physical currency handling. Additionally, integration with Google Firebase facilitates real-time communication between the ESP32 and Razorpay, ensuring that the system accurately verifies payments and reflects transaction status without delay. This results in a smooth, user-friendly payment process.

#### 4.5 Evidence of Payment Verification
A standout feature of the system is its ability to verify payments in real-time using Google Firebase as a cloud-based database. Firebase updates instantly once the transaction is complete, sending confirmation to the ESP32 microcontroller, which then triggers the product dispensing mechanism if the payment is successful. The entire process from payment to dispensing occurs within seconds, ensuring that users do not face unnecessary delays. This integration ensures that transactions are securely validated before any product is dispensed, preventing accidental or fraudulent dispensations.

##### 1. Successful Transaction Data
   For successful transactions, Firebase receives the transaction data and once the payment status is verified as successful, the system triggers the product dispensing action. Below figure 4.7 is a snapshot of the data retrieved from Firebase for a successful transaction:
   #### **Figure 4.7: Payment Captured Status**
   ![captured](https://github.com/user-attachments/assets/8d34a51f-8704-4aca-8260-22bc3458bb76)
   


This data is retrieved in real-time by the ESP32 and used to trigger the product dispensing mechanism. When the payment status is captured as ’payment.success’, the payment is considered valid, and the dispensing action is triggered. This seamless payment verification process ensures that only successful payments lead to the dispensing of products, preventing any errors or fraudulent transactions.

##### 2. Failed Transaction Data
   For failed transactions, the data is captured and stored in Firebase which is shown in figure 4.8 below:
   #### **Figure 4.8: Payment Failed Status**

   ![failed](https://github.com/user-attachments/assets/76390fe8-cd82-4f71-b81c-e36495a2de4a)


When the payment status is captured as ’payment.failed’, the system recognizes the transaction as unsuccessful. In this case, no dispensing action is triggered, ensuring that no product is dispensed without a valid payment. This process helps maintain the integrity and security of the system by preventing fraudulent or incomplete transactions.

#### 4.6 System Performance
The system demonstrates consistent and reliable performance throughout its operations. The Wi-Fi communication between the ESP32, Firebase and Razorpay is stable, ensuring that all components work in sync without any major connectivity issues. The delay between product selection, payment initiation and product dispensing is minimal, usually taking only a few seconds to complete all actions. This fast processing time enhances user satisfaction by ensuring that there are no long waits for transactions to complete. The system’s performance under various conditions, including multiple users and simultaneous transactions, proves its efficiency and scalability for practical use in automated vending machines or similar applications.

#### 4.7 Major Milestones and Issues
Throughout the development of the IoT-enabled payment gateway system, several key milestones were achieved, along with challenges that had to be overcome to ensure the system functioned as expected.

Wi-Fi and Firebase Communication: One of the initial hurdles was establishing stable communication between the ESP32 and Firebase. A reliable Wi-Fi connection was essential for real-time payment verification. The first challenge encountered was Wi-Fi instability, which was resolved by optimizing network configurations, ensuring proper authentication, and ensuring the network was secure. Once stable, the ESP32 was able to reliably send and receive data from Firebase, which was crucial for payment status updates and product dispensing actions.

Razorpay Integration: Integrating Razorpay into the system for secure payment processing was a major milestone. However, handling real-time webhook data from Razorpay posed challenges. The payment status from Razorpay needed to be accurately fetched and relayed to Firebase for validation, which required continuous testing and debugging. Ensuring that the system could efficiently handle the webhook data and communicate with Firebase without delays or data inconsistencies was critical for seamless payment verification.

User Interface Design: The development of the user interface was another essential aspect of the project. The TFT display had to show clear instructions, QR codes for payments, and real-time payment updates. One of the challenges here was ensuring the interface was intuitive and responsive, especially in dynamically displaying QR codes based on the selected product amount.

Product Dispensing Mechanism: Ensuring that the product dispensing mechanism was triggered appropriately after a successful payment was one of the most critical milestones. The synchronization between hardware and software was vital to guarantee no delays between payment confirmation and product dispensing. This process involved real-time communication between the ESP32 and Firebase, ensuring the transaction status was correctly verified before triggering the dispensing action.

Project Progression: The project started with a simple task of lighting up an LED to confirm a successful transaction. This served as a foundational step before moving on to more complex tasks. The next major step was dynamically displaying the QR code on the TFT display based on the payment amount and ensuring that payment verification occurred accurately. Once the transaction details were confirmed, attention shifted to automating the product dispensing mechanism, which was successfully implemented.

Through iterative testing and debugging, the system was refined to ensure it performed consistently, resulting in a fully functional IoT-enabled payment gateway system with seamless payment processing and product dispensing.


### **5. Conclusion and Future Work**

This project demonstrates the successful development of a payment gateway on an IoT-enabled device and vending machine, showcasing the system’s potential. It integrates modern technologies to enable efficient, seamless cashless transactions. The system is built around the ESP32 microcontroller, managing core functions like product selection, payment processing, and dispensing. Key hardware components, including push buttons, a TFT LCD, a product dispensing mechanism, and a buzzer, create an intuitive user experience. Cloud-based services like Google Firebase handle real-time transaction management, while Razorpay’s payment gateway facilitates secure, dynamic QR code generation for UPI or mobile wallet payments.

The process starts with the user selecting a product via a push-button interface, with the selected product displayed on the TFT screen. Pre-generated QR codes stored in the ESP32 allow users to scan and complete payments. Razorpay sends payment information to Firebase, which the ESP32 monitors for updates. Upon payment confirmation, the ESP32 triggers the dispensing mechanism. The system was developed using a structured methodology, ensuring smooth communication between ESP32, Firebase, and Razorpay, with Wi-Fi connectivity and HTTP security. Custom firmware was created for the ESP32 to manage all functions, while Firebase handled transaction data and Razorpay processed payments. The system was rigorously tested to ensure minimal delays in payment processing and dispensing. Each step, from product selection to dispensing, is completed efficiently, highlighting the system’s real-world viability. The user interface, with real-time feedback, ensures ease of interaction.

This project integrates IoT and secure payment processing to streamline cashless transactions for automated product dispensing. Combining QR codes, secure payment gateways, and an IoT microcontroller enables seamless, contactless transactions, enhancing user convenience. This approach demonstrates the potential for IoT-enabled payment gateways in various systems.

As for future work, several enhancements can be explored, such as:
• Adding support for additional gateways would provide more payment options, enhancing accessibility and convenience.
• Expanding the system to handle a wider variety of products or applying it in areas like retail kiosks or automated counters would increase its commercial potential across IoT-driven applications.
• Adding stronger error-handling features would help the system manage problems like lost connections, payment issues, or device malfunctions more effectively, making it more reliable.



