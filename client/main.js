function main() {
  console.log("welcome to fictional lamp");

  const form = document.getElementById("fictional-lamp-form");

  const iceCreamInput = form.querySelector("input");

  form.addEventListener("submit", (e) => {
    e.preventDefault();

    const data = { favoriteIceCream: iceCreamInput.value };

    fetch("http://localhost:8080/data", {
      method: "POST",
      mode: "cors",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(data),
    })
      .then((response) => response.json())
      .then((json) => {
        console.log("Success:", json);
      })
      .catch((error) => {
        console.error("Error:", error);
      });
  });
}

main();
