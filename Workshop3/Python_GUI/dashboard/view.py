import pygame, sys

WHITE = (255,255,255)
BACK_GREY = (52, 58, 64)
FRONT_GREY = (81, 90, 99)

class DataComponent(object):
    def __init__(self, value=0.0, symbol=""):
        self.value = float(value)
        self.symbol = str(symbol)
        self.font = pygame.font.Font(None, 64)

    def set_value(self, new_value):
        self.value = new_value

    def get_text(self):
        return "%.1f %s" % (self.value, self.symbol)

    def render(self, window, centerx, centery, width, height):
        text = self.font.render(self.get_text(), 1, WHITE)
        pygame.draw.polygon(window, FRONT_GREY, (
                            (centerx-width/2, centery-height/2),
                            (centerx+width/2, centery-height/2),
                            (centerx+width/2, centery+height/2),
                            (centerx-width/2, centery+height/2)))
        textRect = text.get_rect(centerx=centerx, centery=centery)
        window.blit(text, textRect)

class DashboardView(object):
    def __init__(self, **kwargs):
        pygame.init()
        self.size = kwargs['size'] if 'size' in kwargs else (400,200)
        self.window = pygame.display.set_mode(self.size, 0 , 32)
        self.events = {}
        self.components = {}
        self.components["temp"] = DataComponent(0.0, "°C")
        self.components["volt"] = DataComponent(0.0, "V")

    def render(self):
        self.window.fill(BACK_GREY)
        data_order = ["volt","temp"]
        for i in range(len(data_order)):
            data = data_order[i]
            centerx = (self.window.get_width() * (2*i + 1)) / (2 * len(data_order))
            centery = self.window.get_height() / 2
            width = (self.window.get_width() / len(data_order)) - 20
            height = self.window.get_height() - 20
            self.components[data].render(self.window, centerx, centery, width, height)
        pygame.display.update()

    def bind_event(self, event, func):
        self.events[str(event)] = func

    def handle_events(self):
        for event in pygame.event.get():
            if str(event.type) in self.events:
                self.events[str(event.type)]()

    def close(self):
        pygame.quit()


