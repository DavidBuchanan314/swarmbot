import serial
import pygame
import sys

if len(sys.argv) != 2:
	print("USAGE: {} [serial device]".format(sys.argv[0]))
	exit()

pygame.init()
pygame.display.set_caption("Remote Controller")
screen = pygame.display.set_mode([640, 480])
clock = pygame.time.Clock()

ser = serial.Serial(sys.argv[1], 115200)

while True:
	pressed = pygame.key.get_pressed()
	if pressed[pygame.K_d]:
		ser.write(b'd')
	elif pressed[pygame.K_a]:
		ser.write(b'a')
	elif pressed[pygame.K_s]:
		ser.write(b's')
	elif pressed[pygame.K_w]:
		ser.write(b'w')
	else:
		ser.write(b'x')
	pygame.event.pump()
	clock.tick(120);
