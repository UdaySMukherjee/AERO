
var swiper = new Swiper(".reviews-slider", {
  direction: "horizontal", // Slide direction is set to horizontal
  loop: true,
  spaceBetween: 30,
  grabCursor: true,
  breakpoints: {
    700: {
      slidesPerView: 1,
    },
    1100: {
      slidesPerView: 2,
    },
  },
  autoplay: {
    delay: 2000, // Delay between slides in milliseconds
    disableOnInteraction: false, // Allow user interaction to stop autoplay
  },
});