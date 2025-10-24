import random

def Dice_game(dice_face):
    #makes it easy to adjust sided dice
    return random.randint(1,dice_face) # make it so the player can change the dice size later
#make it so play game y/n then how many sided face dice?...score

def play_game():
    print(" Let's play a game....Dice Roller!🎲")
    
    player_name = input("User name: ")
    print(f"Let's play player: {player_name}")
        #intialized scoreboard
    total_score = 0
    try: 
        rounds = int(input(f"How many Rounds of the game would you like to play, {player_name}?: "))
        dice_face = int(input("What faced diced do you want to play with? "))
        if dice_face <= 0 or rounds <= 0:
            dice_face = 6
            rounds = 1
            print("Well lets play a round with a normal dice then...")
        
    except ValueError:
        print("Invalid input... setting rounds to...1 and dice to normal")
        rounds = 1
        dice_face =6
    
    #begin game
    for round_num in range(1, rounds + 1):
        print(f"\n Round! {round_num}")
        die1 = Dice_game(dice_face)
        die2 = Dice_game(dice_face)
        print(f' you have rolled a {die1} and a {die2}')
        round_score = die1 + die2
        print(f" Round score {round_score}")

        #score keep for each round
        total_score += round_score
        #wanna quit?
        if round_num != rounds:
            continue_game = input("Do you want to continue? (Y/N): ").lower()
            if continue_game != 'y':
                print("Well you didnt say Y...good bye")
                break

#game is done: final score
    print(f"{player_name}'s final score is {total_score}...Good game!")


#start game
play_game()
