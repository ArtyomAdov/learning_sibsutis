let el = document.querySelectorAll(".root img");
let anime;
let isOn = false;
let i = 500;

let timer = i => {
  anime = setInterval(() => {
    for (let i = 0; i < el.length; i++) {
      if (el[11].id === "seen") {
        el[11].id = " ";
        el[0].setAttribute("id", "seen");
        break;
      }
      if (el[i].id === "seen") {
        el[i].id = " ";
        el[i + 1].setAttribute("id", "seen");
        break;
      }
    }
  }, i);
};

start = () => {
  if (!isOn) {
    isOn = true;
    timer(i);
  }
};

stop = () => {
  if (isOn) {
    isOn = false;
    clearInterval(anime);
  }
};

slower = () => {
  if (isOn) {
    i += 100;
    clearInterval(anime);
    timer(i);
  }
};

faster = () => {
  if (isOn) {
    i -= 100;
    clearInterval(anime);
    timer(i);
  }
};

revers = () => {
  if (!isOn) {
    visOn = false;
    timer(i);
  }
};
