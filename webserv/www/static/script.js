/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.js                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:46:19 by lschweit          #+#    #+#             */
/*   Updated: 2025/03/04 13:48:02 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ======== fly ======

function getRandomPosition(maxWidth, maxHeight)
{
    const x = Math.random() * (maxWidth - 100);
    const y = Math.random() * (maxHeight - 100);
    return { x, y };
}

function moveFly(fly)
{
    const { innerWidth, innerHeight } = window;
    const { x, y } = getRandomPosition(innerWidth, innerHeight);

    fly.style.transition = "all 1s ease";
    fly.style.left = `${x}px`;
    fly.style.top = `${y}px`;
}

document.addEventListener("DOMContentLoaded", () => {
    const fly = document.createElement("img");
    fly.src = "static/fly.png";
    fly.alt = "flying fly";
    fly.style.position = "absolute";
    fly.style.width = "50px";
    fly.style.height = "50px";
    document.body.appendChild(fly);

    const flySound = new Audio("static/flies-buzzing.mp3");
    flySound.loop = true;
    flySound.volume = 0.5;
    flySound.play().catch(() => {
        console.log("Le navigateur a bloqué l'autoplay. Cliquez pour activer le son.");
    });

    document.addEventListener("click", () => {
        flySound.play();
    }, { once: true });


    let intervalId = setInterval(() => moveFly(fly), 1000);

    fly.addEventListener("click", () => {
        clearInterval(intervalId);
        fly.src = "static/deadfly.png";
        fly.style.transition = "none";
        fly.style.pointerEvents = "none";
        
        const splatSound = new Audio("static/splat.mp3");
        splatSound.play();
        
        flySound.pause();
        flySound.currentTime = 0; 

        setTimeout(() => {
            launchConfetti();
        }, 300);
    });
});

function launchConfetti() {
    const duration = 2000;
    const end = Date.now() + duration;

    (function frame() {
        if (Date.now() < end) {
            confetti({
                particleCount: 100,
                angle: Math.random() * 360,
                spread: 60,
                origin: {
                    x: Math.random(),
                    y: Math.random()
                },
                colors: ['#ff0', '#ff6347', '#32cd32', '#4682b4'] 
            });
            requestAnimationFrame(frame);
        }
    })();
}


// == Mode Disco ==

document.addEventListener("DOMContentLoaded", () => {
    const discoButton = document.getElementById("disco-button");
    const body = document.body;
    const discoMusic = document.getElementById("disco-music");

    const colors = ["#f59fe8", "#ffae00", "#eaea6b", "#90f278", "#82c7f6", "#c078f0", "#f367bb"];
    let colorIndex = 0;
    let discoInterval;

    function startDisco() {
        discoInterval = setInterval(() => {
            body.style.backgroundColor = colors[colorIndex];
            colorIndex = (colorIndex + 1) % colors.length; 
        }, 200);
        discoMusic.play();
    }

    function stopDisco() {
        clearInterval(discoInterval);
        body.style.backgroundColor = "white";
        discoMusic.pause();
        discoMusic.currentTime = 0;
    }

    discoButton.addEventListener("click", () => {
        if (discoInterval) {
            stopDisco();
            discoInterval = null;
        } else {
            startDisco();
        }
    });
});


// == Redir wiki Inconnus ==

document.getElementById('histoire-button').addEventListener('click', function() {
    window.location.href = '/inconnu'; 
});


// ===== discoball =====

document.addEventListener("DOMContentLoaded", function() {
    const discoButton = document.getElementById('disco-button');
    const discoBall = document.getElementById('discoBall');
    const discoBallLight = document.getElementById('discoBallLight');

    discoButton.addEventListener('click', function() {
        document.body.classList.toggle('disco-mode');

        if (document.body.classList.contains('disco-mode')) {
            discoBall.style.display = 'block';
            discoBallLight.style.display = 'block';
            discoButton.textContent = 'Mode Normal';
        } else {
            discoBall.style.display = 'none';
            discoBallLight.style.display = 'none';
            discoButton.textContent = 'Mode Disco';
        }
    });

    var t = 1;
    var radius = 200;
    var squareSize = 24;
    var prec = 19.55;
    var fuzzy = 0.001;
    var inc = (Math.PI - fuzzy) / prec;

    for (var t = fuzzy; t < Math.PI; t += inc) {
        var z = radius * Math.cos(t);
        var currentRadius = Math.abs((radius * Math.cos(0) * Math.sin(t)) - (radius * Math.cos(Math.PI) * Math.sin(t))) / 2.5;
        var circumference = Math.abs(2 * Math.PI * currentRadius);
        var squaresThatFit = Math.floor(circumference / squareSize);
        var angleInc = (Math.PI * 2 - fuzzy) / squaresThatFit;
        for (var i = angleInc / 2 + fuzzy; i < (Math.PI * 2); i += angleInc) {
            var square = document.createElement("div");
            var squareTile = document.createElement("div");
            squareTile.style.width = squareSize + "px";
            squareTile.style.height = squareSize + "px";
            squareTile.style.transformOrigin = "0 0 0";
            squareTile.style.transform = "rotate(" + i + "rad) rotateY(" + t + "rad)";
            if ((t > 1.3 && t < 1.9) || (t < -1.3 && t > -1.9)) {
                squareTile.style.backgroundColor = randomColor("bright");
            } else {
                squareTile.style.backgroundColor = randomColor("any");
            }
            square.appendChild(squareTile);
            square.className = "square";
            squareTile.style.animation = "reflect 2s linear infinite";
            squareTile.style.animationDelay = String(randomNumber(0, 20) / 10) + "s";
            squareTile.style.backfaceVisibility = "hidden";
            var x = radius * Math.cos(i) * Math.sin(t);
            var y = radius * Math.sin(i) * Math.sin(t);
            square.style.transform = "translateX(" + x + "px) translateY(" + y + "px) translateZ(" + z + "px)";
            discoBall.appendChild(square);
        }
    }

    function randomColor(type) {
        var c;
        if (type == "bright") {
            c = randomNumber(130, 255);
        } else {
            c = randomNumber(110, 190);
        }
        return "rgb(" + c + "," + c + "," + c + ")";
    }

    function randomNumber(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }
});