let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <Component1 message="Hello!" />
      <Component2 greeting="Hello!" />
    </div>,
};
