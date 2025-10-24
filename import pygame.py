import pygame
import random

# Initialize Pygame
pygame.init()

# Screen settings
WIDTH, HEIGHT = 600, 400
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Number Guessing Game")

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (50, 205, 50)
RED = (255, 0, 0)

# Fonts
font = pygame.font.Font(None, 36)

# Game variables
Ans = random.randint(1, 100)
score = 0
input_text = ""
message = "Guess a number (1-100)"

running = True
while running:
    screen.fill(WHITE)  # Clear screen
    text_surface = font.render(message, True, BLACK)
    screen.blit(text_surface, (20, 50))

    input_surface = font.render(input_text, True, GREEN)
    screen.blit(input_surface, (20, 100))

    pygame.display.flip()  # Update display

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False  # Close the game

        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_RETURN:
                try:
                    guess = int(input_text)
                    score += 1
                    if guess > Ans:
                        message = "Too High! Try again."
                    elif guess < Ans:
                        message = "Too Low! Try again."
                    else:
                        message = f"You Win! Score: {score}"
                        Ans = random.randint(1, 100)  # Reset the game
                        score = 0
                    input_text = ""  # Clear input
                except ValueError:
                    message = "Enter a valid number!"
                    input_text = ""

            elif event.key == pygame.K_BACKSPACE:
                input_text = input_text[:-1]
            else:
                input_text += event.unicode  # Add input text

pygame.quit()
