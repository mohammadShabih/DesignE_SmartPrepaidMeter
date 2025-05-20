The aim of this project is develop a Smart Prepaid Energy Controller, an embedded device which allows fair and accurate control and monitoring of electricity usage. Its intended use is in student rentals, especially in expensive rental
towns such as  Stellenbosch, and other short term rentals. 

The above reposistery is a subsection of the code devloped during the semester, due to university copyright. All code above are ither code written by myself or open source libraries.

Included are hardware and software block diagrams, circuit schematics, state machine diagrams, and adc peripheral diagrams. The usage of the interrupt based shedualer was a project requirement and not chosen by the author. 

Of particular note are the implementation of quadrature modulation to measure analoge signals, which acheived 2% accuracy of Vrms, Irms, and phase. The method button of debouncing used for a 4x3 keypad was also highly succesful, with
zero ghosting or missed keypad presses(the implemtaion used matrix scanning, and EXTI interrupts. Furhter details can be found is the debounce diagram).

The Smart Prepaid included SD card storage system, which is why FATFS is also included in the project.
