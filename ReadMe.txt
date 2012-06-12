
Windows Mobile application to read SIM Card ICC (SIM Serial Number).


ICC is printed on the SIM card with following format:
11111
22222
33333
44444
xxnnn

The executable will run silently and does only work if the WAN modem is ON.
It will write into MSP Attribute registry key if the SIM card can be read successfully.

The value can be found under following registry key:

HKLM\Software\MSP\Attributes
ICC = "1235467890123456"
