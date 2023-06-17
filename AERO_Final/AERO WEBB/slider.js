
var swiper = new Swiper(".reviews-slider", {
  direction: "horizontal", // Slide direction is set to horizontal
  loop: true,
  spaceBetween: 20,
  grabCursor: true,
  breakpoints: {
    600: {
      slidesPerView: 1,
    },
    850: {
      slidesPerView: 2,
    },
    1300: {
      slidesPerView: 3,
    },
  },
  autoplay: {
    delay: 1000, // Delay between slides in milliseconds
    disableOnInteraction: false, // Allow user interaction to stop autoplay
  },
});