type action =
  | Click;

type state = {clicks: int};

let component = ReasonReact.reducerComponent("Component4");

let make = _children => {
  ...component,
  initialState: () => {clicks: 0},
  reducer: (action, state) =>
    switch (action) {
    | Click => ReasonReact.Update({clicks: state.clicks + 1})
    },
  render: self =>
    <div>
      (
        ReasonReact.stringToElement(
          {j|Kliknięcia: |j} ++ string_of_int(self.state.clicks),
        )
      )
      <button onClick=(_e => self.send(Click))>
        (ReasonReact.stringToElement("Kliknij"))
      </button>
    </div>,
};
