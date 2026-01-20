document.addEventListener("DOMContentLoaded", () => {
    const container = document.getElementById("balloon-container");

    if (!container) return;

    const colors = [
        "#ff8fcf",
        "#9a7ff9",
        "#ffd966",
        "#8ed4ff"
    ];

    function explode(x, y, color) {
        const count = 12;

        for (let i = 0; i < count; i++) {
            const p = document.createElement("div");
            p.className = "balloon-particle";

            const angle = (Math.PI * 2 * i) / count;
            const distance = 40 + Math.random() * 30;

            p.style.left = x + "px";
            p.style.top = y + "px";
            p.style.setProperty("--dx", Math.cos(angle) * distance + "px");
            p.style.setProperty("--dy", Math.sin(angle) * distance + "px");
            p.style.setProperty("--particle-color", color);

            document.body.appendChild(p);

            setTimeout(() => p.remove(), 600);
        }
    }

    function createBalloon() {
        const balloon = document.createElement("div");
        balloon.classList.add("balloon");

        const color = colors[Math.floor(Math.random() * colors.length)];
        balloon.style.setProperty("--balloon-color", color);

        balloon.style.left = Math.random() * 90 + "vw";
        balloon.style.animationDuration = (10 + Math.random() * 6) + "s";

        balloon.addEventListener("click", (e) => {
            const rect = balloon.getBoundingClientRect();
            const x = rect.left + rect.width / 2;
            const y = rect.top + rect.height / 2;

            explode(x, y, color);
            balloon.remove();
        });

        container.appendChild(balloon);

        setTimeout(() => balloon.remove(), 16000);
    }

    setInterval(createBalloon, 1200);
});
