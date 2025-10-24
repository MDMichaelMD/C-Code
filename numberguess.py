import random  # Allows me to use the random module

print("Let's play a game!")

while True:
    choice = input("I am thinking of a number between 1 to 100 (whole numbers only), can you guess it? (Y/N): ").strip().upper()

    # Validate input to make sure only "Y" or "N" is accepted
    while choice not in ("Y", "N"):
        print("Invalid choice! Please enter 'Y' or 'N' only.")
        choice = input("I am thinking of a number between 1 to 100 (whole numbers only), can you guess it? (Y/N): ").strip().upper()

    if choice == "Y":  # Start the game
        Ans = random.randint(1, 100)  # Generate a random number
        print("I have my number!")
        print("Smallest score wins!")

        score = 0  # Initialize score at the beginning of each game

        while True:
            try:
                Guess = int(input("What is your guess?: "))  # Convert guess to integer
                score += 1  # Increase score on every guess
                
                if Guess > Ans:
                    print("Too High")
                elif Guess < Ans:
                    print("Too Low")
                else:
                    print("You are correct! You win bragging rights!!!")
                    print(f"Your score is {score}")
                    print("Good-Bye, Champ!")
                    
                    Play_again = input("Would you like to play again? (Y/N): ").strip().upper()

                    # Validate input for replay
                    while Play_again not in ("Y", "N"):
                        print("Invalid choice! Please enter 'Y' or 'N' only.")
                        Play_again = input("Would you like to play again? (Y/N): ").strip().upper()

                    if Play_again == "Y":
                        print("Let's play again!")
                        break  # Restart the game
                    else:
                        print("Bye!")
                        exit()  # Exit the entire game
            
            except ValueError:
                print("Invalid input. Please enter an integer.")

    elif choice == "N":
        print("Game over, I guess. Loser.")
        break  # Exit the game loop
