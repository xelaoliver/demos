# Alex Oliver, 2026
# Display machine usage, run using: flask --app main run

from flask import Flask, jsonify
from psutil import cpu_percent, virtual_memory, swap_memory, cpu_count
from math import ceil
from time import sleep
from threading import Thread

DIALWIDTH = 200
DIALROW = 6

display = []

def update():
    global display

    while 1:
        usages = cpu_percent(interval = 1, percpu = 1)

        newDisplay = []
        
        # cores
        for coreI, coreUsage in enumerate(usages):
            newDisplay.append([coreUsage, f"CORE no. {coreI+1}"])

        # ram
        newDisplay.append([virtual_memory().percent, "MEM"])

        # swap
        newDisplay.append([swap_memory().percent, "SWAP"])

        display = newDisplay

        sleep(.1)

Thread(target=update, daemon=True).start()
app = Flask(__name__)

@app.route("/get-data")
def getData():
    return jsonify(value=display)

@app.route("/")
def main():
    itemCount = (cpu_count() or 1)+2
    canvasHeight = ceil(itemCount/DIALROW)*int(DIALWIDTH*.75+DIALWIDTH*.25)

    return f"""
        <!DOCTYPE html><html>
        <head>
            <title>wozmon</title>
        </head>
        <body>
            <div style="text-align: center; width: 100%;">
                wozmon
                
                <p>
                    <canvas width="{DIALROW*DIALWIDTH}" height="{canvasHeight}" id="canvas"></canvas>
                </p>
            </div>

            <script>
                const canvas = document.getElementById("canvas");
                const ctx = canvas.getContext("2d");

                ctx.textAlign = "center";
                ctx.textBaseline = "middle";

                function trig(r, rad) {{
                    return [Math.cos(rad)*r, -Math.sin(rad)*r];
                }}

                function base(i) {{
                    return i%5 == 0 || i == 24;
                }}

                function dial(x, y, percent, name) {{
                    ctx.translate(x, y);

                    const startRad = 30*(Math.PI/180);
                    const endRad = 150*(Math.PI/180);

                    for (let i = 0; i < 25; i ++) {{
                        const a = startRad+(i*((endRad-startRad)/24));
                        
                        // draw increments
                        ctx.beginPath();
                        ctx.moveTo(...trig(80, a));
                        ctx.lineTo(...trig((base(i)*10)+90, a));
                        ctx.stroke();

                        // units
                        if (base(i)) {{
                            ctx.save();

                            ctx.translate(...trig(70, a));
                            ctx.rotate((Math.PI/2)-a);

                            ctx.fillText((25-(i === 24 ? 25 : i))*4, 0, 0);

                            ctx.restore();
                        }}

                    }}

                    // dial
                    ctx.beginPath();
                    ctx.moveTo(0, 0);
                    ctx.lineTo(...trig(80, endRad-((percent/100)*(endRad-startRad))));
                    ctx.stroke();

                    ctx.fillText(name, 0, 20);

                    ctx.translate(-x, -y);
                }}

                async function get() {{
                    var display = [];
                    try {{
                        const response = await fetch("/get-data");
                        const data = await response.json();

                        display = data.value || [];

                        return display;
                    }} catch (error) {{
                        console.error("error fetching data:", error);
                        return -1;
                    }}
                }}

                async function main() {{
                    const display = await get();

                    ctx.clearRect(0, 0, canvas.width, canvas.height);
                    
                    var x = {DIALWIDTH/2};
                    var y = {DIALWIDTH/2};
                    
                    for (let i = 0; i < display.length; i ++) {{
                        const info = display[i];
                        dial(x, y, info[0], info[1]);
                        
                        if ((i+1) % {DIALROW} == 0) {{
                            x = {DIALWIDTH/2};
                            y += {DIALWIDTH*.75};
                        }} else {{
                            x += {DIALWIDTH};
                        }}
                    }}
                }}

                setInterval(main, 100);
            </script>
        </body>
        </html>
    """
