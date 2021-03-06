#include <pgmspace.h>
char style_css[] PROGMEM = R"=====(
:root{--blue:#375a7f;--indigo:#6610f2;--purple:#6f42c1;--pink:#e83e8c;--red:#E74C3C;--orange:#fd7e14;--yellow:#F39C12;--green:#00bc8c;--teal:#20c997;--cyan:#3498DB;--white:#fff;--gray:#999;--gray-dark:#303030;--primary:#375a7f;--secondary:#444;--success:#00bc8c;--info:#3498DB;--warning:#F39C12;--danger:#E74C3C;--light:#303030;--dark:#adb5bd;--breakpoint-xs:0;--breakpoint-sm:576px;--breakpoint-md:768px;--breakpoint-lg:992px;--breakpoint-xl:1200px;--font-family-sans-serif:"Lato", -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol";--font-family-monospace:SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;}
*,*::before,*::after{-webkit-box-sizing:border-box;box-sizing:border-box;}
html{font-family:sans-serif;line-height:1.15;-webkit-text-size-adjust:100%;-webkit-tap-highlight-color:rgba(0,0,0,0);}
body{margin:0;font-family:"Lato", -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol";font-size:0.9375rem;font-weight:400;line-height:1.5;color:#fff;text-align:left;background-color:#222;}
h4{margin-top:0;margin-bottom:0.5rem;}
p{margin-top:0;margin-bottom:1rem;}
button{border-radius:0;}
button:focus{outline:1px dotted;outline:5px auto -webkit-focus-ring-color;}
button{margin:0;font-family:inherit;font-size:inherit;line-height:inherit;}
button{overflow:visible;}
button{text-transform:none;}
button{-webkit-appearance:button;}
button::-moz-focus-inner{padding:0;border-style:none;}
h4{margin-bottom:0.5rem;font-weight:500;line-height:1.2;}
h4{font-size:1.40625rem;}
.container{width:100%;padding-right:15px;padding-left:15px;margin-right:auto;margin-left:auto;}
@media (min-width: 576px){
.container{max-width:540px;}
}
@media (min-width: 768px){
.container{max-width:720px;}
}
@media (min-width: 992px){
.container{max-width:960px;}
}
@media (min-width: 1200px){
.container{max-width:1140px;}
}
.btn{display:inline-block;font-weight:400;color:#fff;text-align:center;vertical-align:middle;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none;background-color:transparent;border:1px solid transparent;padding:0.375rem 0.75rem;font-size:0.9375rem;line-height:1.5;border-radius:0.25rem;-webkit-transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;}
@media (prefers-reduced-motion: reduce){
.btn{-webkit-transition:none;transition:none;}
}
.btn:hover{color:#fff;text-decoration:none;}
.btn:focus{outline:0;-webkit-box-shadow:0 0 0 0.2rem rgba(55,90,127,0.25);box-shadow:0 0 0 0.2rem rgba(55,90,127,0.25);}
.btn:disabled{opacity:0.65;}
.btn-primary{color:#fff;background-color:#375a7f;border-color:#375a7f;}
.btn-primary:hover{color:#fff;background-color:#2b4764;border-color:#28415b;}
.btn-primary:focus{-webkit-box-shadow:0 0 0 0.2rem rgba(85,115,146,0.5);box-shadow:0 0 0 0.2rem rgba(85,115,146,0.5);}
.btn-primary:disabled{color:#fff;background-color:#375a7f;border-color:#375a7f;}
.btn-success{color:#fff;background-color:#00bc8c;border-color:#00bc8c;}
.btn-success:hover{color:#fff;background-color:#009670;border-color:#008966;}
.btn-success:focus{-webkit-box-shadow:0 0 0 0.2rem rgba(38,198,157,0.5);box-shadow:0 0 0 0.2rem rgba(38,198,157,0.5);}
.btn-success:disabled{color:#fff;background-color:#00bc8c;border-color:#00bc8c;}
.btn-warning{color:#fff;background-color:#F39C12;border-color:#F39C12}
.btn-warning:hover{color:#fff;background-color:#d4860b;border-color:#c87f0a}
.btn-warning:focus,.btn-warning.focus{-webkit-box-shadow:0 0 0 0.2rem rgba(245,171,54,0.5);box-shadow:0 0 0 0.2rem rgba(245,171,54,0.5)}
.btn-warning:disabled{color:#fff;background-color:#F39C12;border-color:#F39C12;}
.btn-danger{color:#fff;background-color:#E74C3C;border-color:#E74C3C;}
.btn-danger:hover{color:#fff;background-color:#e12e1c;border-color:#d62c1a;}
.btn-danger:focus{-webkit-box-shadow:0 0 0 0.2rem rgba(235,103,89,0.5);box-shadow:0 0 0 0.2rem rgba(235,103,89,0.5);}
.btn-danger:disabled{color:#fff;background-color:#E74C3C;border-color:#E74C3C;}
.navbar{position:relative;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding:1rem 1rem;}
.navbar>.container{display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;}
.navbar-brand{display:inline-block;padding-top:0.32421875rem;padding-bottom:0.32421875rem;margin-right:1rem;font-size:1.171875rem;line-height:inherit;white-space:nowrap;}
.navbar-brand:hover,.navbar-brand:focus{text-decoration:none;}
@media (max-width: 991.98px){
.navbar-expand-lg>.container{padding-right:0;padding-left:0;}
}
@media (min-width: 992px){
.navbar-expand-lg{-webkit-box-orient:horizontal;-webkit-box-direction:normal;-ms-flex-flow:row nowrap;flex-flow:row nowrap;-webkit-box-pack:start;-ms-flex-pack:start;justify-content:flex-start;}
.navbar-expand-lg>.container{-ms-flex-wrap:nowrap;flex-wrap:nowrap;}
}
.navbar-dark .navbar-brand{color:#fff;}
.navbar-dark .navbar-brand:hover,.navbar-dark .navbar-brand:focus{color:#fff;}
.card{position:relative;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;min-width:0;word-wrap:break-word;background-color:#303030;background-clip:border-box;border:1px solid rgba(0,0,0,0.125);border-radius:0.25rem;}
.card-body{-webkit-box-flex:1;-ms-flex:1 1 auto;flex:1 1 auto;padding:1.25rem;}
.card-title{margin-bottom:0.75rem;}
.card-text:last-child{margin-bottom:0;}
.badge{display:inline-block;padding:0.25em 0.4em;font-size:75%;font-weight:700;line-height:1;text-align:center;white-space:nowrap;vertical-align:baseline;border-radius:0.25rem;-webkit-transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;}
@media (prefers-reduced-motion: reduce){
.badge{-webkit-transition:none;transition:none;}
}
.badge:empty{display:none;}
.badge-success{color:#fff;background-color:#00bc8c;}
.badge-danger{color:#fff;background-color:#E74C3C;}
.bg-primary{background-color:#375a7f!important;}
.mr-3{margin-right:1rem!important;}
.mb-3{margin-bottom:1rem!important;}
@media print{
*,*::before,*::after{text-shadow:none!important;-webkit-box-shadow:none!important;box-shadow:none!important;}
p{orphans:3;widows:3;}
body{min-width:992px!important;}
.container{min-width:992px!important;}
.navbar{display:none;}
.badge{border:1px solid #000;}
}
.slider {
  -webkit-appearance: none;
  width: 100%;
  height: 10px;
  border-radius: 5px;  
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}
.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  border-radius: 50%; 
  background: #00bc8c;
  cursor: pointer;
}
.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  border-radius: 50%;
  background: #00bc8c;
  cursor: pointer;
}
.form-control {
  display: block;
  width: 100%;
  height: calc(2.25rem + 2px);
  padding: 0.375rem 0.75rem;
  font-size: 1rem;
  line-height: 1.5;
  color: #495057;
  background-color: #fff;
  background-clip: padding-box;
  border: 1px solid #ced4da;
  border-radius: 0.25rem;
  transition: border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
}
@media screen and (prefers-reduced-motion: reduce) {
  .form-control {
    transition: none;
  }
}
.form-control::-ms-expand {
  background-color: transparent;
  border: 0;
}
.form-control:focus {
  color: #495057;
  background-color: #fff;
  border-color: #80bdff;
  outline: 0;
  box-shadow: 0 0 0 0.2rem rgba(0, 123, 255, 0.25);
}
.form-control::-webkit-input-placeholder {
  color: #6c757d;
  opacity: 1;
}
.form-control::-moz-placeholder {
  color: #6c757d;
  opacity: 1;
}
.form-control:-ms-input-placeholder {
  color: #6c757d;
  opacity: 1;
}
.form-control::-ms-input-placeholder {
  color: #6c757d;
  opacity: 1;
}
.form-control::placeholder {
  color: #6c757d;
  opacity: 1;
}
.form-control:disabled, .form-control[readonly] {
  background-color: #e9ecef;
  opacity: 1;
}
select.form-control:focus::-ms-value {
  color: #495057;
  background-color: #fff;
}
.form-control-file,
.form-control-range {
  display: block;
  width: 100%;
}
.form-control-plaintext {
  display: block;
  width: 100%;
  padding-top: 0.375rem;
  padding-bottom: 0.375rem;
  margin-bottom: 0;
  line-height: 1.5;
  color: #212529;
  background-color: transparent;
  border: solid transparent;
  border-width: 1px 0;
}
.form-control-plaintext.form-control-sm, .form-control-plaintext.form-control-lg {
  padding-right: 0;
  padding-left: 0;
}
.form-control-sm {
  height: calc(1.8125rem + 2px);
  padding: 0.25rem 0.5rem;
  font-size: 0.875rem;
  line-height: 1.5;
  border-radius: 0.2rem;
}
.form-control-lg {
  height: calc(2.875rem + 2px);
  padding: 0.5rem 1rem;
  font-size: 1.25rem;
  line-height: 1.5;
  border-radius: 0.3rem;
}
select.form-control[size], select.form-control[multiple] {
  height: auto;
}
textarea.form-control {
  height: auto;
}
.was-validated .form-control:valid, .form-control.is-valid, .was-validated
.custom-select:valid,
.custom-select.is-valid {
  border-color: #28a745;
}
.was-validated .form-control:valid:focus, .form-control.is-valid:focus, .was-validated
.custom-select:valid:focus,
.custom-select.is-valid:focus {
  border-color: #28a745;
  box-shadow: 0 0 0 0.2rem rgba(40, 167, 69, 0.25);
}
.was-validated .form-control:valid ~ .valid-feedback,
.was-validated .form-control:valid ~ .valid-tooltip, .form-control.is-valid ~ .valid-feedback,
.form-control.is-valid ~ .valid-tooltip, .was-validated
.custom-select:valid ~ .valid-feedback,
.was-validated
.custom-select:valid ~ .valid-tooltip,
.custom-select.is-valid ~ .valid-feedback,
.custom-select.is-valid ~ .valid-tooltip {
  display: block;
}
.was-validated .form-control-file:valid ~ .valid-feedback,
.was-validated .form-control-file:valid ~ .valid-tooltip, .form-control-file.is-valid ~ .valid-feedback,
.form-control-file.is-valid ~ .valid-tooltip {
  display: block;
}
.was-validated .form-control:invalid, .form-control.is-invalid, .was-validated
.custom-select:invalid,
.custom-select.is-invalid {
  border-color: #dc3545;
}
.was-validated .form-control:invalid:focus, .form-control.is-invalid:focus, .was-validated
.custom-select:invalid:focus,
.custom-select.is-invalid:focus {
  border-color: #dc3545;
  box-shadow: 0 0 0 0.2rem rgba(220, 53, 69, 0.25);
}
.was-validated .form-control:invalid ~ .invalid-feedback,
.was-validated .form-control:invalid ~ .invalid-tooltip, .form-control.is-invalid ~ .invalid-feedback,
.form-control.is-invalid ~ .invalid-tooltip, .was-validated
.custom-select:invalid ~ .invalid-feedback,
.was-validated
.custom-select:invalid ~ .invalid-tooltip,
.custom-select.is-invalid ~ .invalid-feedback,
.custom-select.is-invalid ~ .invalid-tooltip {
  display: block;
}
.was-validated .form-control-file:invalid ~ .invalid-feedback,
.was-validated .form-control-file:invalid ~ .invalid-tooltip, .form-control-file.is-invalid ~ .invalid-feedback,
.form-control-file.is-invalid ~ .invalid-tooltip {
  display: block;
}
.form-inline .form-control {
  display: inline-block;
  width: auto;
  vertical-align: middle;
}
.form-inline .form-control-plaintext {
  display: inline-block;
}
.input-group > .form-control,
.input-group > .custom-select,
.input-group > .custom-file {
  position: relative;
  -ms-flex: 1 1 auto;
  flex: 1 1 auto;
  width: 1%;
  margin-bottom: 0;
}
.input-group > .form-control + .form-control,
.input-group > .form-control + .custom-select,
.input-group > .form-control + .custom-file,
.input-group > .custom-select + .form-control,
.input-group > .custom-select + .custom-select,
.input-group > .custom-select + .custom-file,
.input-group > .custom-file + .form-control,
.input-group > .custom-file + .custom-select,
.input-group > .custom-file + .custom-file {
  margin-left: -1px;
}
.input-group > .form-control:focus,
.input-group > .custom-select:focus,
.input-group > .custom-file .custom-file-input:focus ~ .custom-file-label {
  z-index: 3;
}
.input-group > .custom-file .custom-file-input:focus {
  z-index: 4;
}
.input-group > .form-control:not(:last-child),
.input-group > .custom-select:not(:last-child) {
  border-top-right-radius: 0;
  border-bottom-right-radius: 0;
}
.input-group > .form-control:not(:first-child),
.input-group > .custom-select:not(:first-child) {
  border-top-left-radius: 0;
  border-bottom-left-radius: 0;
}
.input-group-lg > .form-control,
.input-group-lg > .input-group-prepend > .input-group-text,
.input-group-lg > .input-group-append > .input-group-text,
.input-group-lg > .input-group-prepend > .btn,
.input-group-lg > .input-group-append > .btn {
  height: calc(2.875rem + 2px);
  padding: 0.5rem 1rem;
  font-size: 1.25rem;
  line-height: 1.5;
  border-radius: 0.3rem;
}
.input-group-sm > .form-control,
.input-group-sm > .input-group-prepend > .input-group-text,
.input-group-sm > .input-group-append > .input-group-text,
.input-group-sm > .input-group-prepend > .btn,
.input-group-sm > .input-group-append > .btn {
  height: calc(1.8125rem + 2px);
  padding: 0.25rem 0.5rem;
  font-size: 0.875rem;
  line-height: 1.5;
  border-radius: 0.2rem;
}
)=====";
