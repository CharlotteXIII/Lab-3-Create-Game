import pygame



#Window
pygame.init()
window_width = 800
window_height = 600
window = pygame.display.set_mode((window_width, window_height))
pygame.display.set_caption("Touhou")
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Update game state
    # ...

    # Draw game objects
    window.fill((255, 255, 255))  # Clear the window with white color
    # Draw your game objects here
    pygame.display.update()  # Update the display

# Quit Pygame
pygame.quit()