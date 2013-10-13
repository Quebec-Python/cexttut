# Created By: Virgil Dupras
# Created On: 2008-04-20
# Copyright 2013 Hardcoded Software (http://www.hardcoded.net)

# This software is licensed under the "BSD" License as described in the "LICENSE" file, 
# which should be included with this package. The terms are also available at 
# http://www.hardcoded.net/licenses/bsd_license

from datetime import date

class Currency:
    all = []
    by_code = {}
    by_name = {}

    def __new__(cls, code=None, name=None):
        """Returns the currency with the given code."""
        assert (code is None and name is not None) or (code is not None and name is None)
        if code is not None:
            try:
                return cls.by_code[code]
            except KeyError:
                raise ValueError('Unknown currency code: %r' % code)
        else:
            try:
                return cls.by_name[name]
            except KeyError:
                raise ValueError('Unknown currency name: %r' % name)

    def __getnewargs__(self):
        return (self.code,)
 
    def __getstate__(self):
        return None
  
    def __setstate__(self, state):
        pass

    def __repr__(self):
        return '<Currency %s>' % self.code

    @staticmethod
    def register(code, name, exponent=2, start_date=None, start_rate=1, stop_date=None, latest_rate=1):
        """Registers a new currency and returns it."""
        assert code not in Currency.by_code
        assert name not in Currency.by_name
        currency = object.__new__(Currency)
        currency.code = code
        currency.name = name
        currency.exponent = exponent
        currency.start_date = start_date
        currency.start_rate = start_rate
        currency.stop_date = stop_date
        currency.latest_rate = latest_rate
        Currency.by_code[code] = currency
        Currency.by_name[name] = currency
        Currency.all.append(currency)
        return currency

BUILTIN_CURRENCIES = {
# In order we want to list them
Currency.register('USD', 'U.S. dollar',
    start_date=date(1998, 1, 2), start_rate=1.425, latest_rate=1.0128),
Currency.register('EUR', 'European Euro',
    start_date=date(1999, 1, 4), start_rate=1.8123, latest_rate=1.3298),
Currency.register('CAD', 'Canadian dollar',
    latest_rate=1),
Currency.register('JPY', 'Japanese yen',
    exponent=0, start_date=date(1998, 1, 2), start_rate=0.01076, latest_rate=0.01076),
Currency.register('CZK', 'Czech Republic koruna',
    start_date=date(1998, 2, 2), start_rate=0.04154, latest_rate=0.05202),
Currency.register('TND', 'Tunisian dinar',
    exponent=3, start_date=date(1998, 1, 2), start_rate=1.2372, latest_rate=0.7037),
Currency.register('BHD', 'Bahraini dinar',
    exponent=3, start_date=date(2008, 11, 8), start_rate=3.1518, latest_rate=2.6603),
Currency.register('PLN', 'Polish zloty',
    start_date=date(1998, 2, 2), start_rate=0.4108, latest_rate=0.3382),
}
BUILTIN_CURRENCY_CODES = {c.code for c in BUILTIN_CURRENCIES}

# For legacy purpose, we need to maintain these global variables
CAD = Currency(code='CAD')
USD = Currency(code='USD')
EUR = Currency(code='EUR')
