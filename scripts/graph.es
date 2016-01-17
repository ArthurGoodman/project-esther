width = 80;
height = 25;
scale = 1.2;
timeStep = 0.05;
a = -5.0;
b = 5.0;
step = 0.02;
time = 0.0
dir = true

function draw {
    x = if dir a.clone() else b.clone()

    while (if dir x <= b else x >= a) {
        fx = Math.fresnelC(x * Math.cos(time))
        fy = Math.fresnelS(x * Math.sin(time))

        setConsoleCursorPosition((fx * scale + 1) / 2 * width, (-fy * scale + 1) / 2 * height);
        print("+")

        if dir x += step else x += -step
    }

    time += timeStep

    dir = !dir
}

while (true) {
    system("cls")
    draw()
    sleep(33)
}
