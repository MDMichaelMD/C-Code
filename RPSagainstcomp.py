#Rock paper scissors  against computer

import random
#Define choices
choices = ('SCISSORS', 'ROCK', 'PAPER')
emojis = { 'ROCK': '🪨', 'SCISSORS': '✂️', 'PAPER': '📃'}
#Ask if user wants to play
while True: # starts aloop to play
    play = input("Do you want to play? (Y/N): ").strip().upper()
    if play == "Y":
        #generate value
        computer_choice = random.choice(choices)
        #Ask user for their choice
        user_input = input("Rock, Paper, or Scissors?").strip().upper()
        #Validate user input
        if user_input not in choices:
            print("Invalid input please choose Rock, Paper, or Scissors.")
            continue
        print(f"The computer chose: {emojis[computer_choice]}")
        print(f"you picked: {emojis[user_input]}")            
        if computer_choice == user_input:
            print("its a tie!")
        elif ((user_input == 'ROCK' and computer_choice == 'SCISSORS') or
              (user_input == 'PAPER' and computer_choice == 'ROCK') or
              (user_input == 'SCISSORS' and computer_choice == 'PAPER')):
            print("You win!")
        else:
            print("Loser!")
            #ask user if they want to keep on playing
        while True:
            should_continue = input("Continue? (y/n)").lower()
            if should_continue == "n":
                print("Good-bye")
                exit() # end program
            else:  #continue game if any other choice
                break
        
    else: #choice N
        print("Do not waste my time")
        break
