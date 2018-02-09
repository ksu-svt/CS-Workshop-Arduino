import pygame, sys
from dashboard.view import DashboardView
from dashboard.arduino import ArduinoConnection

dashboard = DashboardView(size=(600,400))

def update_data(data):
    print(data)
    dashboard.components["temp"].set_value(data["temp"])
    dashboard.components["volt"].set_value(data["voltage"])
    dashboard.render()


connection = ArduinoConnection(update_data)
connection.start()

def exit():
    connection.close()
    dashboard.close()
    sys.exit()

dashboard.bind_event(pygame.QUIT, exit)
dashboard.render()

#Run the game loop
while True:
    dashboard.handle_events()