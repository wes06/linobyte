# LINOBYTE


## Motivation and Description

As computational devices evolve, more tools and interfaces are built between the user and the machine. This allows us to complete increasingly complex tasks without having to focus so much on understanding the nuances of the machine. While this movement is certainly overall positive, one of the drawbacks is that people no longer learn the fundamental processes and concepts which allow the tool to work. Another negative aspect is that, by neglecting history, we forget the alternatives of the technologies that we use today - forgotten alternatives that maybe once were the status quo. Understanding of those alternatives would give us a broader view of the pros and cons of what we have today, how they superseded their ancestors and what are their pitfalls - important knowledge for those who design possible futures.

Its with these preocupations in mind that Linobyte came into existence. It conciliates the explanation of how bits, bytes and chars work, with a hands on experience of creating Core Rope ROMs: read-only memories that were written by weaving an enameled copper wire through ferrite cores. 

The whole process is quite straightforward, and the result is immediate: the user can write up to 8 characters - a word, in the Linobyte system. Each character consists of one eight-bit byte. Each core represents one bit, and by weaving the conductive wire through the core center, the user sets a bit as positive. By skipping the core, its set as zero. By connecting the wire to the final position, the byte is written. So, if the user wants to write the "A" character, she/he checks the table, to see that "A" is 65 in decimal, 41 in HEX, and 01000001 in binary. Thus, the first (least significant bit) and seventh bit have to be set. She/he then proceeds to the next char, and so forth. After each char is set, it appears on a display, so the user can check whether the bits were correctly set and proceed or correct if necessary.



## Preliminary Functional Block Diagram

![Preliminary Functional Block Diagram](./Img/Block%20Diagrams/preliminary-block-diagram.png)




## To dos

1. Sketch weave "needle" and connection, can't use magnets cause ferrites are magnetic, minor annoyance when weaving..
2. Footprint for magnetic latch switch (magnet, 3xpogo, magnet: pcb switches and 3way and gate?), and/or find out how to attack magnets to PCBs.
3. Switch for external coils
4. Decide how to drive the coils (VCO + LSD?)
5. Add simulations to readme





Teaching how bits form bytes and then characters with a hands on approach.

An homage and revival of core rope memories.

Instead of pressing a button to make a letter or touching a screen, you weave a wire. Handwritting, etc



Pulse generator/ Capacitor in series? / Primary / secondary / full bridge / capacitor / resistor/zener regulator schmitt trigger? / I2C 



## Refs

aulis.com/pascal.htm



http://drhart.ucoz.com/index/core_memory/0-123

http://www.ciphersbyritter.com/MARK8/MAGCORE/MAGCORE.HTM


http://qrp.gr/coreROM/

ROD ROM
http://www.computerculture.org/2012/10/jacquard-looms-and-rod-roms/


Neil on how transformers work.
https://electronics.stackexchange.com/a/221279/61257


### Comparators:

Maxim App note 3616, Adding extra histeresis to comparators  
https://www.maximintegrated.com/en/app-notes/index.mvp/id/3616

Texas Instruments: Comparator with histeresis reference design  
http://www.ti.com/lit/ug/tidu020a/tidu020a.pdf


## BOM

Potential coils: 9mm x 16mm x 5mm (inner, outer, thickness)  
https://www2.mouser.com/Passive-Components/Ferrites/Ferrite-Toroids-Ferrite-Rings/_/N-fb8t7Z1yzvvqx?P=1ya7hnoZ1z0vsmwZ1z0vsssZ1z0vsa5Z1z0vsltZ1z0vrn7&Rl=fb8t7ZerbuZ1yxgwg4Z1yzmqroSGT&Ns=Inside%20Diameter|1

AP331  
Single Differential Comparator  
https://www2.mouser.com/ProductDetail/Diodes-Incorporated/AP331AWG-7?qs=sGAEpiMZZMuayl%2fEk2kXcbfp56RBiQa%252bBYTJGtoHiWw%3d

Kemet ESD - R Series

Schmitt Trigger Octal Non Inverting  
https://www.mouser.at/ProductDetail/Nexperia/74HC7541PW118?qs=sGAEpiMZZMtOwpHsRTkso4N4DgL6o1r6unaSV%252bVDkdI%3d

3 to 8 decoder  
74HC138  
https://www.mouser.at/datasheet/2/302/74HC_HCT138-1148685.pdf

Card edge 20 Pos connector  
https://www.digikey.com/product-detail/en/te-connectivity-amp-connectors/5-5530843-0/A31722-ND/770548

e-ink  
296x128 2.9in  
https://www.amazon.de/Waveshare-Resolution-Electronic-Controller-interface/dp/B071LGVVL1/ref=sr_1_1?rps=1&ie=UTF8&qid=1523130359&sr=8-1&keywords=e+paper+arduino&refinements=p_76%3A419122031