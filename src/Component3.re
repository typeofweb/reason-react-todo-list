[@bs.module "polish-plurals"]
external polishPlurals :
  (
    ~singularNominativ: string,
    ~pluralNominativ: string,
    ~pluralGenitive: string,
    ~value: int,
    unit
  ) =>
  string =
  "";

type action =
  | Tick;

type state = {
  startTime: float,
  currentTime: float,
};

let component = ReasonReact.reducerComponent("Component3");

let getSecondsLabel =
  polishPlurals(
    ~singularNominativ={j|sekundę|j},
    ~pluralNominativ="sekundy",
    ~pluralGenitive="sekund",
  );

let make = _children => {
  ...component,
  initialState: () => {
    let time = Js.Date.now();
    {startTime: time, currentTime: time};
  },
  reducer: (action, state) =>
    switch (action) {
    | Tick => ReasonReact.Update({...state, currentTime: Js.Date.now()})
    },
  subscriptions: ({send}) => [
    Sub(
      () => Js.Global.setInterval(() => send(Tick), 100),
      Js.Global.clearInterval,
    ),
  ],
  render: ({state: {startTime, currentTime}}) => {
    let seconds = int_of_float((currentTime -. startTime) /. 1000.);
    let label = getSecondsLabel(~value=seconds, ());
    let text = {j|Jesteś na tej stronie już: $seconds $label!|j};
    <div> (ReasonReact.stringToElement(text)) </div>;
  },
};
