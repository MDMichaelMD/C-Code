#Dice roller
import random

def Dice_game():
    while True: # begins endless game until N
        Choice = input("do you want to roll the dice? Y/N: ").lower()
        if Choice == "y":
            print("Rolling...Dice...")
            value = random.randint(1,6)
            print(f"I rolled a {value}")
            
        elif Choice =="n":
            print("I will miss you---Good bye!")
            break
        else:
            print("Invalide choice:: N or Y only please")
Dice_game()