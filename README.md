# Events, 
### Ver: 1.2
Events Displays important dates according to the specific month. If there are no arguments, the current month will be used.

The month may be specified as a 3 letter month name, such as Jun or Apr. The months are case sensitive, however you can capitalize the first letter. A full list of months are displayed bellow under *Months*.

There a special color codes that you can customize your date file with, see **Codes** for more information.

## Months
Accepted 3 letter months are as follows: 

| Month        | 3 month code |
|--------------|:------------:|
| January      |  Jan         |
| February     |  Feb         |
| March        |  Mar         |
| April        |  Apr         |
| May          |  May         |
| June         |  Jun         |
| July         |  Jul         |
| August       |  Aug         |
| September    |  Sep         |
| October      |  Oct         |
| November     |  Nov         |
| December     |  Dec         |

## File Format

The events program uses a file in your home directory called `events.txt`. To add a date or an event...simply edit the events.txt file.
For Example, a basic usage: 
```
Dec    25th_Xmas
Mnth   string^^^
```
Or a more realistic example:
```
Dec    25th,_Christmas!
May    19th,_Wifes_birthday
```
*Note:* Something special to note is that the first letter of the month must be a capitalized letter.
The underscore will be replaced as a space once the program runs. 

## Codes

These are special highlight codes that allow you to highlight special events under different colors. These color codes should be added at the very end of the string in the date file. The supported color codes are as follows:
| Codes | What it does          | Example Usage              |
|-------|:---------------------:|:--------------------------:|
| `*`	  | Inverted highlight    | `Dec   23rd,_Festivus_*`   |
| `*B*`	| Blue color highligt   | `Dec   23rd,_Festivus_*B*` |
| `*Y*`	| Yellow color highligt | `Dec   23rd,_Festivus_*Y*` |
| `*G*`	| Green color highligt  | `Dec   23rd,_Festivus_*G*` |
| `*R*`	| Red color highligt    | `Dec   23rd,_Festivus_*R*` |
| `*BL*`| Blink!                | `Dec   23rd,_Festivus_*BL*`|

## Flags

There are only 2 optional flags. `-h or --help`. Both provide a man page style help, that is more or less an exact copy of this Readme document.

## Making / installing
```
make
sudo make install
```
