document.addEventListener("DOMContentLoaded", () => {
  const carousels = document.querySelectorAll("[data-carousel]");

  carousels.forEach((carousel) => {
    const track = carousel.querySelector("[data-track]");
    const prevBtn = carousel.querySelector("[data-prev]");
    const nextBtn = carousel.querySelector("[data-next]");

    if (!track || !prevBtn || !nextBtn) return;

    // Défilement par “page” (80% de la largeur visible)
    const scrollAmount = () => Math.floor(track.clientWidth * 0.8);

    const updateButtons = () => {
      const maxScrollLeft = track.scrollWidth - track.clientWidth;

      // petits arrondis pour éviter les bugs de float
      const left = Math.ceil(track.scrollLeft);

      prevBtn.disabled = left <= 0;
      nextBtn.disabled = left >= Math.floor(maxScrollLeft);
    };

    prevBtn.addEventListener("click", () => {
      track.scrollBy({ left: -scrollAmount(), behavior: "smooth" });
    });

    nextBtn.addEventListener("click", () => {
      track.scrollBy({ left: scrollAmount(), behavior: "smooth" });
    });

    track.addEventListener("scroll", () => {
      // throttle léger
      window.requestAnimationFrame(updateButtons);
    });

    window.addEventListener("resize", updateButtons);

    updateButtons();
  });
});