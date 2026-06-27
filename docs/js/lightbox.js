
// code by ChatGPT

const galleryImages = document.querySelectorAll(".gallery img");

const lightbox = document.getElementById("lightbox");
const lightboxImage = document.getElementById("lightbox-image");

galleryImages.forEach(img => {
    img.addEventListener("click", () => {
        lightboxImage.src = img.src;
        lightbox.classList.add("show");
    });
});

lightbox.addEventListener("click", () => {
    lightbox.classList.remove("show");
});

document.addEventListener("keydown", e => {
    if (e.key === "Escape") {
        lightbox.classList.remove("show");
    }
});