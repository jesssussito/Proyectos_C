
function trace(msg) {
  traceOn = false;
  if (traceOn) {
    return console.log(msg);
  }
}

// MODIFICA ESTO:

const _FIRST_NAME_PATTERN = /modifica_esto/i;
const _LAST_NAME_PATTERN = /modifica_esto/i;
const _DOB_PATTERN = /modifica_esto/i;
const _MOBILE_NUMBER_PATTERN = /modifica_esto/i;
const _PASSWORD_PATTERN = /modifica_esto/i;
const _EMAIL_PATTERN = /modifica_esto/i;


function setUpValidation() {

  let inputs = $(".validate");
  for (let i = 0; i < inputs.length; i++) {

    validateAndSetClass(inputs[i]);
    addEventListenerToInput(inputs[i]);

  }
  return true;
}

function validateAndSetClass(input) {

  if (input.id === "firstName") {
    testInputAndSetClass(input, _FIRST_NAME_PATTERN);
  }

  if (input.id === "lastName") {
    testInputAndSetClass(input, _LAST_NAME_PATTERN);
  }

  if (input.id === "mobileNumber") {
    testInputAndSetClass(input, _MOBILE_NUMBER_PATTERN);
  }

  if (input.id === "password") {
    testInputAndSetClass(input, _PASSWORD_PATTERN);
  }

  if (input.id === "email") {
    testInputAndSetClass(input, _EMAIL_PATTERN);
  }

  if (input.id === "dateOfBirth") {
    testInputAndSetClass(input, _DOB_PATTERN);
  }

  return input;
}

function testInputAndSetClass(input, pattern) {

  // AQUÍ SE ESTÁ UTILIZANDO pattern.test("valor introducido usuario")
  // Si la expresión REGEX se cumple se añade la clase CSS is-valid (que hará que se ponga en verde)
  // En caso contrario is-invalid
  if (pattern.test(input.value)) {
    input.classList.remove('is-invalid');
    input.classList.add('is-valid');

  } else {
    input.classList.remove('is-valid');
    input.classList.add('is-invalid');
  }
}

function addEventListenerToInput(input) {
  input.addEventListener('input', function () {
    validateAndSetClass(input);
    verifyValidation();
  });
}

function addEventListenerToButton(button) {
  document.getElementById(button).addEventListener('click', function () {
    if (this.id === "autoFillButton") {
      autoFillFunction();
    }
    if (this.id === "showRegexButton") {
      showRegexPatterns()
      window.location.href = "#regexMsg";
    }
  })
}

function verifyValidation() {
  let inputs = $(".validate");
  let validInputArray = $(".is-valid");

  if (validInputArray.length == inputs.length) {

    $("#submitButton").removeAttr("disabled");
    $(".succes-msg").show();

    trace("Validation complete!")
  }
}

function autoFillFunction() {
  // Create a new 'change' event
  var event = new Event('input');

  $(".validate")[0].value = "Sergio"
  $(".validate")[0].dispatchEvent(event);
  $(".validate")[1].value = "García González"
  $(".validate")[1].dispatchEvent(event);
  $(".validate")[2].value = "01-01-1991"
  $(".validate")[2].dispatchEvent(event);
  $(".validate")[3].value = "+34 666555444"
  $(".validate")[3].dispatchEvent(event);
  $(".validate")[4].value = "0123456789aA!"
  $(".validate")[4].dispatchEvent(event);
  $(".validate")[5].value = "sergio.gg@usal.es"
  $(".validate")[5].dispatchEvent(event);

}

function showRegexPatterns() {
  if (($("#regexMsg").hasClass("collapse"))) {

    $("#regexMsg").removeClass("collapse");
  } else {
    $("#regexMsg").addClass("collapse");
  }
  
}